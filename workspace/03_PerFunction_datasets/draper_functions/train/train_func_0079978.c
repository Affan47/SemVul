str_concat (lua_State *L) {
  luaL_Buffer b;
  size_t lsep;
  const char *sep = luaL_optlstring(L, 2, "", &lsep);
  int i = luaL_optint(L, 3, 1);
  int n = luaL_optint(L, 4, 0);
  luaL_checktype(L, 1, LUA_TTABLE);
  if (n == 0) n = luaL_getn(L, 1);
  luaL_buffinit(L, &b);
  for (; i <= n; i++) {
    lua_rawgeti(L, 1, i);
    luaL_argcheck(L, lua_isstring(L, -1), 1, "table contains non-strings");
    luaL_addvalue(&b);
    if (i != n)
      luaL_addlstring(&b, sep, lsep);
  }
  luaL_pushresult(&b);
  return 1;
}
