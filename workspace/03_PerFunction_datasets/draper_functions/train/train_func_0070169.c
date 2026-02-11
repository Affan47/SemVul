luaB_print (lua_State *L) {
  int n = lua_gettop(L);
  int i;
  lua_getglobal(L, "tostring");
  for (i=1; i<=n; i++) {
    const char *s;
    size_t l;
    lua_pushvalue(L, -1);
    lua_pushvalue(L, i);
    lua_call(L, 1, 1);
    s = lua_tolstring(L, -1, &l);
    if (s == NULL)
      return luaL_error(L, "'tostring' must return a string to 'print'");
    if (i>1) lua_writestring("\t", 1);
    lua_writestring(s, l);
    lua_pop(L, 1);
  }
  lua_writeline();
  return 0;
}
