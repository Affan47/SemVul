lua_rawsetp (lua_State *L, int idx, const void *p) {
  StkId o;
  Table *t;
  TValue k;
  lua_lock(L);
  api_checknelems(L, 1);
  o = index2addr(L, idx);
  api_check(ttistable(o), "table expected");
  t = hvalue(o);
  setpvalue(&k, cast(void *, p));
  setobj2t(L, luaH_set(L, t, &k), L->top - 1);
  luaC_barrierback(L, t, L->top - 1);
  L->top--;
  lua_unlock(L);
}
