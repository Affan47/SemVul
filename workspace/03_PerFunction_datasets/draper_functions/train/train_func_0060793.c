lj_dispatch_ins(lua_State *L, const BCIns *pc)
{
  ERRNO_SAVE
  GCfunc *fn = curr_func(L);
  GCproto *pt = funcproto(fn);
  void *cf = cframe_raw(L->cframe);
  const BCIns *oldpc = cframe_pc(cf);
  global_State *g = G(L);
  BCReg slots;
  setcframe_pc(cf, pc);
  slots = cur_topslot(pt, pc, cframe_multres_n(cf));
  L->top = L->base + slots;
#if LJ_HASJIT
  {
    jit_State *J = G2J(g);
    if (J->state != LJ_TRACE_IDLE) {
#ifdef LUA_USE_ASSERT
      ptrdiff_t delta = L->top - L->base;
#endif
      J->L = L;
      lj_trace_ins(J, pc-1);
      lua_assert(L->top - L->base == delta);
    }
  }
#endif
  if ((g->hookmask & LUA_MASKCOUNT) && g->hookcount == 0) {
    g->hookcount = g->hookcstart;
    callhook(L, LUA_HOOKCOUNT, -1);
    L->top = L->base + slots;
  }
  if ((g->hookmask & LUA_MASKLINE)) {
    BCPos npc = proto_bcpos(pt, pc) - 1;
    BCPos opc = proto_bcpos(pt, oldpc) - 1;
    BCLine line = lj_debug_line(pt, npc);
    if (pc <= oldpc || opc >= pt->sizebc || line != lj_debug_line(pt, opc)) {
      callhook(L, LUA_HOOKLINE, line);
      L->top = L->base + slots;
    }
  }
  if ((g->hookmask & LUA_MASKRET) && bc_isret(bc_op(pc[-1])))
    callhook(L, LUA_HOOKRET, -1);
  ERRNO_RESTORE
}
