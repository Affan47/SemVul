asm_snap_alloc1(ASMState *as, IRRef ref)
{
  IRIns *ir = IR(ref);
  if (!irref_isk(ref) && (!(ra_used(ir) || ir->r == RID_SUNK))) {
    if (ir->r == RID_SINK) {
      ir->r = RID_SUNK;
#if LJ_HASFFI
      if (ir->o == IR_CNEWI) {
	asm_snap_alloc1(as, ir->op2);
	if (LJ_32 && (ir+1)->o == IR_HIOP)
	  asm_snap_alloc1(as, (ir+1)->op2);
      } else
#endif
      {
	IRIns *irs;
	lua_assert(ir->o == IR_TNEW || ir->o == IR_TDUP || ir->o == IR_CNEW);
	for (irs = IR(as->snapref-1); irs > ir; irs--)
	  if (irs->r == RID_SINK && asm_sunk_store(as, ir, irs)) {
	    lua_assert(irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
		       irs->o == IR_FSTORE || irs->o == IR_XSTORE);
	    asm_snap_alloc1(as, irs->op2);
	    if (LJ_32 && (irs+1)->o == IR_HIOP)
	      asm_snap_alloc1(as, (irs+1)->op2);
	  }
      }
    } else {
      RegSet allow;
      if (ir->o == IR_CONV && ir->op2 == IRCONV_NUM_INT) {
	IRIns *irc;
	for (irc = IR(as->curins); irc > ir; irc--)
	  if ((irc->op1 == ref || irc->op2 == ref) &&
	      !(irc->r == RID_SINK || irc->r == RID_SUNK))
	    goto nosink;
	asm_snap_alloc1(as, ir->op1);
	return;
      }
    nosink:
      allow = (!LJ_SOFTFP && irt_isfp(ir->t)) ? RSET_FPR : RSET_GPR;
      if ((as->freeset & allow) ||
	       (allow == RSET_FPR && asm_snap_canremat(as))) {

	Reg r = ra_allocref(as, ref, allow);
	if (!irt_isphi(ir->t))
	  ra_weak(as, r);
	checkmclim(as);
	RA_DBGX((as, "snapreg   $f $r", ref, ir->r));
      } else {
	ra_spill(as, ir);
	RA_DBGX((as, "snapspill $f $s", ref, ir->s));
      }
    }
  }
}
