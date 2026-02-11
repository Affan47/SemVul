inet_meth_getsockname(lua_State *L, p_socket ps, int family)
{
    int err;
    struct sockaddr_storage peer;
    socklen_t peer_len = sizeof(peer);
    char name[INET6_ADDRSTRLEN];
    char port[6];
    if (getsockname(*ps, (SA *) &peer, &peer_len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(errno));
        return 2;
    }
	err=getnameinfo((struct sockaddr *)&peer, peer_len,
		name, INET6_ADDRSTRLEN, port, 6, NI_NUMERICHOST | NI_NUMERICSERV);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, gai_strerror(err));
        return 2;
    }
    lua_pushstring(L, name);
    lua_pushstring(L, port);
    if (family == PF_INET) {
        lua_pushliteral(L, "inet");
    } else if (family == PF_INET6) {
        lua_pushliteral(L, "inet6");
    } else {
        lua_pushliteral(L, "uknown family");
    }
    return 3;
}
