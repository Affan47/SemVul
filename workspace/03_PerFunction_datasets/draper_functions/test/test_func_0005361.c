searcher_Lua (lua_State *L) {
  const char *filename;
  const char *name = luaL_checkstring(L, 1);
  filename = findfile(L, name, "path", LUA_LSUBSEP);
  if (filename == NULL) return 1;
  return checkload(L, (luaL_loadfile(L, filename) == LUA_OK), filename);
}
