luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
    long long elapsed;
    REDIS_NOTUSED(ar);
    REDIS_NOTUSED(lua);

    elapsed = (ustime()/1000) - server.lua_time_start;
    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
        server.lua_timedout = 1;


         aeDeleteFileEvent(server.el, server.lua_caller->fd, AE_READABLE);
    }
    if (server.lua_timedout)
        aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
    if (server.lua_kill) {
        redisLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
        lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
        lua_error(lua);
    }
}
