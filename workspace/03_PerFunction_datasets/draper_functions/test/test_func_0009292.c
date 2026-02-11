luaD_call (lua_State *L, StkId func, int nResults, int allowyield) {
  if (++L->nCcalls >= LUAI_MAXCCALLS) {
    if (L->nCcalls == LUAI_MAXCCALLS)
      luaG_runerror(L, "C stack overflow");
    else if (L->nCcalls >= (LUAI_MAXCCALLS + (LUAI_MAXCCALLS>>3)))
      luaD_throw(L, LUA_ERRERR);
  }
  if (!allowyield) L->nny++;
  if (!luaD_precall(L, func, nResults))
    luaV_execute(L);
  if (!allowyield) L->nny--;
  L->nCcalls--;
}
