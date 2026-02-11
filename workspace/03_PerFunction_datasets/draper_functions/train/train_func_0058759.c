isIntegerThm(const Expr& e) {

  if(isReal(e.getType())) return Theorem();

  return isIntegerDerive(Expr(IS_INTEGER, e), typePred(e));
}
