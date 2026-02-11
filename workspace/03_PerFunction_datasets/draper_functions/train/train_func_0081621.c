resume (lua_State *L, void *ud) {
  int nCcalls = L->nCcalls;
  StkId firstArg = cast(StkId, ud);
  CallInfo *ci = L->ci;
  if (nCcalls >= LUAI_MAXCCALLS)
    resume_error(L, "C stack overflow", firstArg);
  if (L->status == LUA_OK) {
    if (ci != &L->base_ci)
      resume_error(L, "cannot resume non-suspended coroutine", firstArg);

    if (!luaD_precall(L, firstArg - 1, LUA_MULTRET))
      luaV_execute(L);
  }
  else if (L->status != LUA_YIELD)
    resume_error(L, "cannot resume dead coroutine", firstArg);
  else {
    L->status = LUA_OK;
    ci->func = restorestack(L, ci->extra);
    if (isLua(ci))
      luaV_execute(L);
    else {
      if (ci->u.c.k != NULL) {
        int n;
        lua_unlock(L);
        n = (*ci->u.c.k)(L, LUA_YIELD, ci->u.c.ctx);
        lua_lock(L);
        api_checknelems(L, n);
        firstArg = L->top - n;
      }
      luaD_poscall(L, firstArg);
    }
    unroll(L, NULL);
  }
  lua_assert(nCcalls == L->nCcalls);
}
