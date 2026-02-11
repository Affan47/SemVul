parse_assignment(LexState *ls, LHSVarList *lh, BCReg nvars)
{
  ExpDesc e;
  checkcond(ls, VLOCAL <= lh->v.k && lh->v.k <= VINDEXED, LJ_ERR_XSYNTAX);
  if (lex_opt(ls, ',')) {
    LHSVarList vl;
    vl.prev = lh;
    expr_primary(ls, &vl.v);
    if (vl.v.k == VLOCAL)
      assign_hazard(ls, lh, &vl.v);
    checklimit(ls->fs, ls->level + nvars, LJ_MAX_XLEVEL, "variable names");
    parse_assignment(ls, &vl, nvars+1);
  } else {
    BCReg nexps;
    lex_check(ls, '=');
    nexps = expr_list(ls, &e);
    if (nexps == nvars) {
      if (e.k == VCALL) {
	if (bc_op(*bcptr(ls->fs, &e)) == BC_VARG) {
	  ls->fs->freereg--;
	  e.k = VRELOCABLE;
	} else {
	  e.u.s.info = e.u.s.aux;
	  e.k = VNONRELOC;
	}
      }
      bcemit_store(ls->fs, &lh->v, &e);
      return;
    }
    assign_adjust(ls, nvars, nexps, &e);
    if (nexps > nvars)
      ls->fs->freereg -= nexps - nvars;
  }

  expr_init(&e, VNONRELOC, ls->fs->freereg-1);
  bcemit_store(ls->fs, &lh->v, &e);
}
