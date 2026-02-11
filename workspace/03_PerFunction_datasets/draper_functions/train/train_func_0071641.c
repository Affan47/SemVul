expandGrayShadowRewrite(const Expr& theShadow) {

  if(CHECK_PROOFS) {
    CHECK_SOUND(isGrayShadow(theShadow),
		"ArithTheoremProducerOld::expandGrayShadowConst: not a shadow" +
		theShadow.toString());
  }

  const Rational& c1 = theShadow[2].getRational();
  const Rational& c2 = theShadow[3].getRational();

  if(CHECK_PROOFS) {
    CHECK_SOUND(c1.isInteger() && c2.isInteger() && c1 < c2,
		"ArithTheoremProducerOld::expandGrayShadow: " +
		theShadow.toString());
  }

  const Expr& v = theShadow[0];
  const Expr& e = theShadow[1];

  Proof pf;
  if(withProof())
    pf = newPf("expand_gray_shadow", theShadow);
  Expr ineq1(leExpr(e+rat(c1), v));
  Expr ineq2(leExpr(v, e+rat(c2)));
  return newRWTheorem(theShadow, ineq1 && ineq2, Assumptions::emptyAssump(), pf);
}
