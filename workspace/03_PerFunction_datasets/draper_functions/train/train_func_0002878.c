lua_rawseti (lua_State *L, int idx, lua_Integer n) {
  StkId o;
  Table *t;
  lua_lock(L);
  api_checknelems(L, 1);
  o = index2addr(L, idx);
  api_check(ttistable(o), "table expected");
  t = hvalue(o);
  luaH_setint(L, t, n, L->top - 1);
  luaC_barrierback(L, t, L->top-1);
  L->top--;
  lua_unlock(L);
}
