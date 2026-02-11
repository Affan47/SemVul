rewriteNotOr(const Expr& e) {
  if(CHECK_PROOFS)
    CHECK_SOUND(e.isNot() && e[0].isOr(),
		"rewriteNotOr: precondition violated: " + e.toString());
  vector<Expr> kids;
  for(Expr::iterator i=e[0].begin(), iend=e[0].end(); i!=iend; ++i)

    kids.push_back(i->negate());
  Proof pf;
  if(withProof())
    pf = newPf("rewrite_not_or", e);
  return newRWTheorem(e, andExpr(kids), Assumptions::emptyAssump(), pf);
}
