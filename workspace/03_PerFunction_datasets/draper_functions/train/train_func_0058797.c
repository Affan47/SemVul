canonMultConstSum(const Expr& c1, const Expr& sum) {
  Proof pf;
  std::vector<Expr> sumKids;

  if(CHECK_PROOFS) {
    CHECK_SOUND(isRational(c1),
                CLASS_NAME "::canonMultConstTerm:\n  "
                "c1 is not a constant: " + c1.toString());
    CHECK_SOUND(PLUS == sum.getKind(),
                CLASS_NAME "::canonMultConstTerm:\n  "
                "the kind must be a PLUS: " + sum.toString());
  }
  Expr::iterator i = sum.begin();
  for(; i != sum.end(); ++i)
    sumKids.push_back(c1*(*i));
  Expr ret = plusExpr(sumKids);
  if(withProof()) pf = newPf("canon_mult_const_sum", c1, sum, ret);
  return newRWTheorem((c1*sum),ret , Assumptions::emptyAssump(), pf);
}
