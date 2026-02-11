asm_snap_checkrename(ASMState *as, IRRef ren)
{
  SnapShot *snap = &as->T->snap[as->snapno];
  SnapEntry *map = &as->T->snapmap[snap->mapofs];
  MSize n, nent = snap->nent;
  for (n = 0; n < nent; n++) {
    SnapEntry sn = map[n];
    IRRef ref = snap_ref(sn);
    if (ref == ren || (LJ_SOFTFP && (sn & SNAP_SOFTFPNUM) && ++ref == ren)) {
      IRIns *ir = IR(ref);
      ra_spill(as, ir);
      RA_DBGX((as, "snaprensp $f $s", ref, ir->s));
      return 1;
    }
  }
  return 0;
}
