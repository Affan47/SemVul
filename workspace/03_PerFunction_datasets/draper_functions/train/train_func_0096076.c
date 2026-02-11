clashingBounds(const Theorem& lowerBound, const Theorem& upperBound) {


	const Expr& lowerBoundExpr = lowerBound.getExpr();
	const Expr& upperBoundExpr = upperBound.getExpr();


	if (CHECK_PROOFS) {
		CHECK_SOUND(isLE(lowerBoundExpr) || isLT(lowerBoundExpr), "clashingBounds: lowerBound should be >= or > " + lowerBoundExpr.toString());
		CHECK_SOUND(isGE(upperBoundExpr) || isGT(upperBoundExpr), "clashingBounds: upperBound should be <= or < " + upperBoundExpr.toString());
		CHECK_SOUND(lowerBoundExpr[0].isRational(), "clashingBounds: lowerBound left side should be a rational " + lowerBoundExpr.toString());
		CHECK_SOUND(upperBoundExpr[0].isRational(), "clashingBounds: upperBound left side should be a rational " + upperBoundExpr.toString());
		CHECK_SOUND(lowerBoundExpr[1] == upperBoundExpr[1], "clashingBounds: bounds not on the same term " + lowerBoundExpr.toString() + ", " + upperBoundExpr.toString());


		Rational lowerBoundR = lowerBoundExpr[0].getRational();
		Rational upperBoundR = upperBoundExpr[0].getRational();

		if (isLE(lowerBoundExpr) && isGE(upperBoundExpr)) {
			CHECK_SOUND(upperBoundR < lowerBoundR, "clashingBounds: bounds are satisfiable");
		} else {
			CHECK_SOUND(upperBoundR <= lowerBoundR, "clashingBounds: bounds are satisfiable");
		}
	}


	Proof pf;

	if (withProof())
		pf = newPf("clashingBounds", lowerBoundExpr, upperBoundExpr);


	Assumptions assumptions;
	assumptions.add(lowerBound);
	assumptions.add(upperBound);


	return newTheorem(d_em->falseExpr(), assumptions, pf);
}
