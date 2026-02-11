parse_simple_body (LexState *ls, ExpDesc *fne, int line) {
  FuncState fs, *pfs = ls->fs;
  FuncScope bl;
  BCReg kidx;
  BCLine lastline;
  GCproto *pt;
  ptrdiff_t oldbase = pfs->bcbase - ls->bcstack;
  BCIns ins;
  ExpDesc e;

  fs_init(ls, &fs);
  fscope_begin(&fs, &bl, 0);
  fs.linedefined = line;
  fs.numparams = (uint8_t)parse_params_ext(ls, 0, '|', '|');
  fs.bcbase = pfs->bcbase + pfs->pc;
  fs.bclim = pfs->bclim - pfs->pc;
  bcemit_AD(&fs, BC_FUNCF, 0, 0);

  fs.flags |= PROTO_HAS_RETURN;
  expr(ls, &e);
  ins = BCINS_AD(BC_RET1, expr_toanyreg(&fs, &e), 2);
  if (fs.flags & PROTO_CHILD)
    bcemit_AJ(&fs, BC_UCLO, 0, 0);
  bcemit_INS(&fs, ins);

  lastline = ls->linenumber;
  pt = fs_finish(ls, lastline);
  pfs->bcbase = ls->bcstack + oldbase;
  pfs->bclim = (BCPos)(ls->sizebcstack - oldbase);

  kidx = const_gc(pfs, obj2gco(pt), LJ_TPROTO);
  expr_init(fne, VRELOCABLE, bcemit_AD(pfs, BC_FNEW, 0, kidx));
#if LJ_HASFFI
  pfs->flags |= (fs.flags & PROTO_FFI);
#endif
  if (!(pfs->flags & PROTO_CHILD)) {
    if (pfs->flags & PROTO_HAS_RETURN)
      pfs->flags |= PROTO_FIXUP_RETURN;
    pfs->flags |= PROTO_CHILD;
  }
}
