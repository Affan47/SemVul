rewriteNotIff(const Expr& e) {
  Proof pf;
  if(CHECK_PROOFS)
    CHECK_SOUND(e.isNot() && e[0].isIff(), "rewriteNotIff precondition violated");
  if(withProof()) {
    pf = newPf("rewrite_not_iff", e);
  }
  return newRWTheorem(e, e[0][0].iffExpr(!e[0][1]), Assumptions::emptyAssump(), pf);
}
