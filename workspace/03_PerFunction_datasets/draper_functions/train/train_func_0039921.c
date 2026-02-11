report(lua_State* L)
{
    const char* msg = lua_tostring(L, -1);
    while (msg)
    {
        lua_pop(L, 1);
        ELUNA_LOG_ERROR("%s", msg);
        msg = lua_tostring(L, -1);
    }
}
