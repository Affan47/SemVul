lua_yield (lua_State *L, int nresults) {
  CallInfo *ci;
  lua_lock(L);
  ci = L->ci;
  if (L->nCcalls > 0)
    luaG_runerror(L, "attempt to yield across metamethod/C-call boundary");
  if (ci->state & CI_C) {
    if ((ci-1)->state & CI_C)
      luaG_runerror(L, "cannot yield a C function");
    if (L->top - nresults > L->base) {
      int i;
      for (i=0; i<nresults; i++)
        setobjs2s(L->base + i, L->top - nresults + i);
      L->top = L->base + nresults;
    }
  }
  ci->state |= CI_YIELD;
  lua_unlock(L);
  return -1;
}
