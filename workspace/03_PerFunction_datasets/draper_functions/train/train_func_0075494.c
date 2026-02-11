mp_encode_lua_number(lua_State *L, mp_buf *buf) {
    lua_Number n = lua_tonumber(L,-1);

    if (floor(n) != n) {
        mp_encode_double(buf,(double)n);
    } else {
        mp_encode_int(buf,(int64_t)n);
    }
}
