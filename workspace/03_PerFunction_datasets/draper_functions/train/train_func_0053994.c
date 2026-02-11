sort (lua_State *L) {
  int n = aux_getn(L, 1);
  luaL_checkstack(L, 40, "");
  if (!lua_isnoneornil(L, 2))
    luaL_checktype(L, 2, LUA_TFUNCTION);
  lua_settop(L, 2);
  auxsort(L, 1, n);
  return 0;
}
