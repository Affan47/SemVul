io_lines (lua_State *L) {
  int toclose;
  if (lua_isnone(L, 1)) lua_pushnil(L);
  if (lua_isnil(L, 1)) {
    lua_getfield(L, LUA_REGISTRYINDEX, IO_INPUT);
    lua_replace(L, 1);
    tofile(L);
    toclose = 0;
  }
  else {
    const char *filename = luaL_checkstring(L, 1);
    opencheck(L, filename, "r");
    lua_replace(L, 1);
    toclose = 1;
  }
  aux_lines(L, toclose);
  return 1;
}
