json_cfg_encode_sparse_array(lua_State *l)
{
    json_config_t *cfg;
    int val;

    json_verify_arg_count(l, 3);
    cfg = json_fetch_config(l);

    switch (lua_gettop(l)) {
    case 3:
        val = luaL_checkinteger(l, 3);
        luaL_argcheck(l, val >= 0, 3, "expected integer >= 0");
        cfg->encode_sparse_safe = val;
    case 2:
        val = luaL_checkinteger(l, 2);
        luaL_argcheck(l, val >= 0, 2, "expected integer >= 0");
        cfg->encode_sparse_ratio = val;
    case 1:
        luaL_argcheck(l, lua_isboolean(l, 1), 1, "expected boolean");
        cfg->encode_sparse_convert = lua_toboolean(l, 1);
    }

    lua_pushboolean(l, cfg->encode_sparse_convert);
    lua_pushinteger(l, cfg->encode_sparse_ratio);
    lua_pushinteger(l, cfg->encode_sparse_safe);

    return 3;
}
