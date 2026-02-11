lua_pcallk (lua_State *L, int nargs, int nresults, int errfunc,
                        int ctx, lua_CFunction k) {
  struct CallS c;
  int status;
  ptrdiff_t func;
  lua_lock(L);
  api_check(L, k == NULL || !isLua(L->ci),
    "cannot use continuations inside hooks");
  api_checknelems(L, nargs+1);
  api_check(L, L->status == LUA_OK, "cannot do calls on non-normal thread");
  checkresults(L, nargs, nresults);
  if (errfunc == 0)
    func = 0;
  else {
    StkId o = index2addr(L, errfunc);
    api_checkstackindex(L, errfunc, o);
    func = savestack(L, o);
  }
  c.func = L->top - (nargs+1);
  if (k == NULL || L->nny > 0) {
    c.nresults = nresults;
    status = luaD_pcall(L, f_call, &c, savestack(L, c.func), func);
  }
  else {
    CallInfo *ci = L->ci;
    ci->u.c.k = k;
    ci->u.c.ctx = ctx;

    ci->extra = savestack(L, c.func);
    ci->u.c.old_allowhook = L->allowhook;
    ci->u.c.old_errfunc = L->errfunc;
    L->errfunc = func;

    ci->callstatus |= CIST_YPCALL;
    luaD_call(L, c.func, nresults, 1);
    ci->callstatus &= ~CIST_YPCALL;
    L->errfunc = ci->u.c.old_errfunc;
    status = LUA_OK;
  }
  adjustresults(L, nresults);
  lua_unlock(L);
  return status;
}
