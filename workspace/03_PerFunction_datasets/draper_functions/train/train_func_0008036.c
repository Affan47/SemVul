lua_verify(lua_State *state) {
    int argc = lua_gettop(state);
    int result;

    if (argc == 1) {
        if (update_source != NULL) {
            result = update_source->verify(update_source);
        }
        else result = EBADF;
    }
    else result = EINVAL;

    lua_pushnumber(state, result);
    return 1;
}
