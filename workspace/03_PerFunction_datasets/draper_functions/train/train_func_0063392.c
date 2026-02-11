lua_next (lua_State *L, int idx) {
  StkId t;
  int more;
  lua_lock(L);
  t = index2adr(L, idx);
  api_check(L, ttistable(t));
  more = luaH_next(L, hvalue(t), L->top - 1);
  if (more) {
    api_incr_top(L);
  }
  else
    L->top -= 1;
  lua_unlock(L);
  return more;
}
