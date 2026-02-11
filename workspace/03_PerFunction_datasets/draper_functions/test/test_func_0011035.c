asm_phi_shuffle(ASMState *as)
{
  RegSet work;


  for (;;) {
    RegSet blocked = RSET_EMPTY;
    RegSet blockedby = RSET_EMPTY;
    RegSet phiset = as->phiset;
    while (phiset) {
      Reg r = rset_pickbot(phiset);
      IRIns *irl = IR(as->phireg[r]);
      Reg left = irl->r;
      if (r != left) {
	if (!rset_test(as->freeset, r)) {
	  IRRef ref = regcost_ref(as->cost[r]);

	  if (!ra_iskref(ref) && irt_ismarked(IR(ref)->t)) {
	    rset_set(blocked, r);
	    if (ra_hasreg(left))
	      rset_set(blockedby, left);
	    left = RID_NONE;
	  } else {
	    ra_restore(as, ref);
	    checkmclim(as);
	  }
	}
	if (ra_hasreg(left)) {
	  ra_rename(as, left, r);
	  checkmclim(as);
	}
      }
      rset_clear(phiset, r);
    }
    if (!blocked) break;
    if (!(as->freeset & blocked)) {
      asm_phi_break(as, blocked, blockedby, RSET_GPR);
      if (!LJ_SOFTFP) asm_phi_break(as, blocked, blockedby, RSET_FPR);
      checkmclim(as);
    }
  }


#if !LJ_SOFTFP
  work = as->modset & ~(as->freeset | as->phiset) & RSET_FPR;
  while (work) {
    Reg r = rset_pickbot(work);
    ra_restore(as, regcost_ref(as->cost[r]));
    rset_clear(work, r);
    checkmclim(as);
  }
#endif
  work = as->modset & ~(as->freeset | as->phiset);
  while (work) {
    Reg r = rset_pickbot(work);
    ra_restore(as, regcost_ref(as->cost[r]));
    rset_clear(work, r);
    checkmclim(as);
  }


  work = as->phiset;
  while (work) {
    Reg r = rset_picktop(work);
    IRRef lref = as->phireg[r];
    IRIns *ir = IR(lref);
    if (ra_hasspill(ir->s)) {
      irt_clearmark(ir->t);
      ra_alloc1(as, lref, RID2RSET(r));
      ra_save(as, ir, r);
      checkmclim(as);
    }
    rset_clear(work, r);
  }
}
