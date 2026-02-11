traceexec (lua_State *L) {
  lu_byte mask = L->hookmask;
  if (mask > LUA_MASKLINE) {
    if (L->hookcount == 0) {
      resethookcount(L);
      luaD_callhook(L, LUA_HOOKCOUNT, -1);
      return;
    }
  }
  if (mask & LUA_MASKLINE) {
    CallInfo *ci = L->ci;
    Proto *p = ci_func(ci)->l.p;
    int newline = getline(p, pcRel(*ci->u.l.pc, p));
    if (!L->hookinit) {
      luaG_inithooks(L);
      return;
    }
    lua_assert(ci->state & CI_HASFRAME);
    if (pcRel(*ci->u.l.pc, p) == 0)
      ci->u.l.savedpc = *ci->u.l.pc;

    if (*ci->u.l.pc <= ci->u.l.savedpc ||
        newline != getline(p, pcRel(ci->u.l.savedpc, p))) {
      luaD_callhook(L, LUA_HOOKLINE, newline);
      ci = L->ci;
    }
    ci->u.l.savedpc = *ci->u.l.pc;
  }
}
