isIntegerDerive(const Expr& isIntE, const Theorem& thm) {
  const Expr& e = thm.getExpr();

  if(e == isIntE) return thm;

  Theorem res;

  if(e.isAnd()) {
    int i, iend=e.arity();
    for(i=0; i<iend; ++i) {
      res = isIntegerDerive(isIntE, getCommonRules()->andElim(thm, i));
      if(!res.isNull()) return res;
    }
  }
  return res;
}
