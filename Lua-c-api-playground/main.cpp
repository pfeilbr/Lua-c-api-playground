//
//  main.cpp
//  Lua-c-api-playground
//
//  Created by Brian Pfeil on 12/31/17.
//  Copyright © 2017 Brian Pfeil. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <string.h>


/*

may need to change to `#include <lua.hpp>` depending on include path

`/usr/local/include` is in include path.  `lua` is subdirectory

tree /usr/local/include/lua
/usr/local/include/lua
├── lauxlib.h
├── lua.h
├── lua.hpp
├── luaconf.h
└── lualib.h

*/
#include <lua/lua.hpp>

// call the print function with a string argument
static void printExample(lua_State *L) {
    lua_getglobal(L, "print");
    lua_pushstring(L, "enter your lua code and press enter");
    lua_pcallk(L, 1, 0, 0, 0, 0);
}

int main(int argc, const char * argv[]) {
    
    char buff[256];
    int error;

    lua_State *L = luaL_newstate();
    
    luaopen_base(L);             /* opens the basic library */
    luaopen_table(L);            /* opens the table library */
    luaopen_io(L);               /* opens the I/O library */
    luaopen_string(L);           /* opens the string lib. */
    luaopen_math(L);             /* opens the math lib. */
    
    printExample(L);
    
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
        lua_pcall(L, 0, 0, 0);
        
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));
            lua_pop(L, 1);  /* pop error message from the stack */
        }
    }
    
    lua_close(L);
    
    return 0;
}
