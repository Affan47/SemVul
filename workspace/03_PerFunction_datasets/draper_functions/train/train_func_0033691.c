rewriteIff(const Expr& e) {
  Proof pf;
  if(CHECK_PROOFS)
    CHECK_SOUND(e.isIff(), "rewriteIff precondition violated");
  if(withProof()) {
    pf = newPf("rewrite_iff", e[0], e[1]);
  }

  if(e[0] == e[1]) return rewriteReflexivity(e);

  switch(e[0].getKind()) {
  case TRUE_EXPR:
    return newRWTheorem(e, e[1], Assumptions::emptyAssump(), pf);
  case FALSE_EXPR:
    return newRWTheorem(e, !e[1], Assumptions::emptyAssump() ,pf);
  case NOT:
    if(e[0][0]==e[1])
      return newRWTheorem(e, d_em->falseExpr(), Assumptions::emptyAssump(), pf);
    break;
  default: break;
  }

  switch(e[1].getKind()) {
  case TRUE_EXPR:
    return newRWTheorem(e, e[0], Assumptions::emptyAssump(), pf);
  case FALSE_EXPR:
    return newRWTheorem(e, !e[0], Assumptions::emptyAssump(), pf);
  case NOT:
    if(e[0]==e[1][0])
      return newRWTheorem(e, d_em->falseExpr(), Assumptions::emptyAssump(), pf);
    break;
  default:
    break;
  }

  if(e[0] < e[1])
    return rewriteUsingSymmetry(e);
  else
    return reflexivityRule(e);
}
