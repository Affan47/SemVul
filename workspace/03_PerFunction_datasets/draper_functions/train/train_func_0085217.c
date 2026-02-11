implyWeakerInequality(const Expr& expr1, const Expr& expr2) {


	if (CHECK_PROOFS) {


		CHECK_SOUND(isIneq(expr1), "implyWeakerInequality: expr1 should be an inequality" + expr1.toString());
		CHECK_SOUND(isIneq(expr2), "implyWeakerInequality: expr1 should be an inequality" + expr2.toString());


		if (isLE(expr1) || isLT(expr1))
			CHECK_SOUND(isLE(expr2) || isLT(expr2), "implyWeakerInequality: expr2 should be <(=) also " + expr2.toString());
		if (isGE(expr1) || isGT(expr1))
			CHECK_SOUND(isGE(expr2) || isGT(expr2), "implyWeakerInequality: expr2 should be >(=) also" + expr2.toString());


		CHECK_SOUND(expr1[0].isRational(), "implyWeakerInequality: expr1 should have a rational on the left side" + expr1.toString());
		CHECK_SOUND(expr2[0].isRational(), "implyWeakerInequality: expr2 should have a rational on the left side" + expr2.toString());


		CHECK_SOUND(expr1[1] == expr2[1], "implyWeakerInequality: the expression must be the same" + expr1.toString() + " and " + expr2.toString());

		Rational expr1rat = expr1[0].getRational();
		Rational expr2rat = expr2[0].getRational();


		if (isLE(expr1) || isLT(expr2)) {
			CHECK_SOUND(expr2rat < expr1rat,  "implyWeakerInequality: the implication doesn't apply" + expr1.toString() + " and " + expr2.toString());
		} else {
			CHECK_SOUND(expr2rat <= expr1rat, "implyWeakerInequality: the implication doesn't apply" + expr1.toString() + " and " + expr2.toString());
		}
		if (isGE(expr1) || isGT(expr2)) {
			CHECK_SOUND(expr2rat > expr1rat,  "implyWeakerInequality: the implication doesn't apply" + expr1.toString() + " and " + expr2.toString());
		} else {
			CHECK_SOUND(expr2rat >= expr1rat, "implyWeakerInequality: the implication doesn't apply" + expr1.toString() + " and " + expr2.toString());
		}
	}


  	Proof pf;
  	if(withProof())	pf = newPf("implyWeakerInequality", expr1, expr2);


	return newTheorem(expr1.impExpr(expr2), Assumptions::emptyAssump(), pf);
}
