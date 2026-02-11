luaB_xpcall (lua_State *L) {
  if (lua_icontext(L) == 0) {
    luaL_checkany(L, 2);
    lua_settop(L, 2);
    lua_insert(L, 1);
  }
  return aux_pcall(L, 1);
}
