searcher_preload (lua_State *L) {
  const char *name = luaL_checkstring(L, 1);
  lua_getfield(L, LUA_REGISTRYINDEX, "_PRELOAD");
  if (lua_getfield(L, -1, name) == LUA_TNIL)
    lua_pushfstring(L, "\n\tno field package.preload['%s']", name);
  return 1;
}
