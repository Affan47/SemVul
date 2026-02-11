sort (lua_State *L) {
  TabA ta;
  int n = (int)aux_getn(L, 1, &ta);
  luaL_checkstack(L, 50, "");
  if (!lua_isnoneornil(L, 2))
    luaL_checktype(L, 2, LUA_TFUNCTION);
  lua_settop(L, 2);
  auxsort(L, &ta, 1, n);
  return 0;
}
