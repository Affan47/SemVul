read_keybind_t(lua_State* L, int index, keybind_t *data)
{
    if (lua_getfield_or_warn(L, index, "name")) {
        read_string(L, -1, &data->name);
        lua_pop(L, 1);
    }
    if (lua_getfield_or_warn(L, index, "key")) {
        read_int32_t(L, -1, &data->key);
        lua_pop(L, 1);
    }
    if (lua_getfield_or_warn(L, index, "mod")) {
        read_int32_t(L, -1, &data->mod);
        lua_pop(L, 1);
    }
}
