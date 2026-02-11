lua_rotate (lua_State *L, int idx, int n) {
  StkId p, t, m;
  lua_lock(L);
  t = L->top - 1;
  p = index2addr(L, idx);
  api_checkstackindex(idx, p);
  api_check((n >= 0 ? n : -n) <= (t - p + 1), "invalid 'n'");
  m = (n >= 0 ? t - n : p - n - 1);
  reverse(L, p, m);
  reverse(L, m + 1, t);
  reverse(L, p, t);
  lua_unlock(L);
}
