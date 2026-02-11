rec_for_loop(jit_State *J, const BCIns *fori, ScEvEntry *scev,
			 int init)
{
  BCReg ra = bc_a(*fori);
  cTValue *tv = &J->L->base[ra];
  TRef idx = J->base[ra+FORL_IDX];
  IRType t = idx ? tref_type(idx) :
	     (init || LJ_DUALNUM) ? lj_opt_narrow_forl(J, tv) : IRT_NUM;
  int mode = IRSLOAD_INHERIT +
    ((!LJ_DUALNUM || tvisint(tv) == (t == IRT_INT)) ? IRSLOAD_READONLY : 0);
  TRef stop = fori_arg(J, fori, ra+FORL_STOP, t, mode);
  TRef step = fori_arg(J, fori, ra+FORL_STEP, t, mode);
  int tc, dir = rec_for_direction(&tv[FORL_STEP]);
  lua_assert(bc_op(*fori) == BC_FORI || bc_op(*fori) == BC_JFORI);
  scev->t.irt = t;
  scev->dir = dir;
  scev->stop = tref_ref(stop);
  scev->step = tref_ref(step);
  rec_for_check(J, t, dir, stop, step, init);
  scev->start = tref_ref(find_kinit(J, fori, ra+FORL_IDX, IRT_INT));
  tc = (LJ_DUALNUM &&
	!(scev->start && irref_isk(scev->stop) && irref_isk(scev->step) &&
	  tvisint(&tv[FORL_IDX]) == (t == IRT_INT))) ?
	IRSLOAD_TYPECHECK : 0;
  if (tc) {
    J->base[ra+FORL_STOP] = stop;
    J->base[ra+FORL_STEP] = step;
  }
  if (!idx)
    idx = fori_load(J, ra+FORL_IDX, t,
		    IRSLOAD_INHERIT + tc + (J->scev.start << 16));
  if (!init)
    J->base[ra+FORL_IDX] = idx = emitir(IRT(IR_ADD, t), idx, step);
  J->base[ra+FORL_EXT] = idx;
  scev->idx = tref_ref(idx);
  setmref(scev->pc, fori);
  J->maxslot = ra+FORL_EXT+1;
}
