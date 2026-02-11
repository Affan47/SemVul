rewriteNotExists(const Expr& e) {
  if(CHECK_PROOFS) {
    CHECK_SOUND(e.isNot() && e[0].isExists(),
		"rewriteNotExists: expr must be NOT FORALL:\n"
		+e.toString());
  }
  Proof pf;
  if(withProof())
    pf = newPf("rewrite_not_exists", e);
  return newRWTheorem(e, d_em->newClosureExpr(FORALL, e[0].getVars(),
                                              !e[0].getBody()), Assumptions::emptyAssump(), pf);
}
