checkupval (lua_State *L, int argf, int argnup) {
  int nup = (int)luaL_checkinteger(L, argnup);
  luaL_checktype(L, argf, LUA_TFUNCTION);
  luaL_argcheck(L, (lua_getupvalue(L, argf, nup) != NULL), argnup,
                   "invalid upvalue index");
  return nup;
}
