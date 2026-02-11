lua_rawseti (lua_State *L, int idx, int n) {
  StkId t;
  lua_lock(L);
  api_checknelems(L, 1);
  t = index2addr(L, idx);
  api_check(L, ttistable(t), "table expected");
  luaH_setint(L, hvalue(t), n, L->top - 1);
  luaC_barrierback(L, gcvalue(t), L->top-1);
  L->top--;
  lua_unlock(L);
}
