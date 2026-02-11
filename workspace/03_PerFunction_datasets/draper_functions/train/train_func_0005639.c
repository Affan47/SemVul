is_disabled(lua_State* L, const char* name)
{
  int status = 0;
  lua_getfield(L, LUA_REGISTRYINDEX, LSB_CONFIG);
  if (lua_type(L, -1) != LUA_TTABLE) {
    lua_pop(L, 1);
    return status;
  }
  lua_getfield(L, -1, "disable_modules");
  if (lua_type(L, -1) != LUA_TTABLE) {
    lua_pop(L, 2);
    return status;
  }
  lua_getfield(L, -1, name);
  if (lua_type(L, -1) != LUA_TNIL) {
    status = 1;
  }
  lua_pop(L, 3);
  return status;
}
