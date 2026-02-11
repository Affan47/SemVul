lua_setlocal (lua_State *L, const lua_Debug *ar, int n) {
  StkId pos = 0;
  const char *name = findlocal(L, ar->i_ci, n, &pos);
  lua_lock(L);
  if (name) {
    setobjs2s(L, pos, L->top - 1);
    L->top--;
  }
  lua_unlock(L);
  return name;
}
