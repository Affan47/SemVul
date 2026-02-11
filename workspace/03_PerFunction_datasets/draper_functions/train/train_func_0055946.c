inet_global_gethostname(lua_State *L)
{
    char name[257];
    name[256] = '\0';
    if (gethostname(name, 256) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(errno));
        return 2;
    } else {
        lua_pushstring(L, name);
        return 1;
    }
}
