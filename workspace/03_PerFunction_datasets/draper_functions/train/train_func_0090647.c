dooptions (lua_State *L, int n) {
  int i;
  for (i = 2; i <= n; i++) {
    lua_pushvalue(L, i);
    lua_pushvalue(L, -2);
    lua_call(L, 1, 0);
  }
}
