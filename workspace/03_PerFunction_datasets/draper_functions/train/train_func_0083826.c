exprstat (LexState *ls) {

  FuncState *fs = ls->fs;
  struct LHS_assign v;
  primaryexp(ls, &v.v);
  if (v.v.k == VCALL)
    SETARG_C(getcode(fs, &v.v), 1);
  else {
    v.prev = NULL;
    assignment(ls, &v, 1);
  }
}
