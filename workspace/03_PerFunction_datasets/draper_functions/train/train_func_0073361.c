getLowerBoundExplanation(const TebleauxMap::iterator& var_it) {

	vector<Theorem> upperBounds;


	Theorem tableauxTheorem = (*var_it).second;


	const Expr& var = (*var_it).first;


	const Expr& rightSide = tableauxTheorem.getExpr()[1];


	int leftSide_i_end = rightSide.arity();
	for(int leftSide_i = 0; leftSide_i < leftSide_i_end; ++ leftSide_i) {


		const Expr& a = rightSide[leftSide_i][0];


		const Expr& x = rightSide[leftSide_i][1];


		if (a.getRational() > 0) {

			Theorem thm = getUpperBoundThm(x);


			thm = iffMP(thm, d_rules->multIneqn(thm.getExpr(), a));


			Theorem canonRight  = d_rules->canonMultTermConst(thm.getExpr()[1][1], thm.getExpr()[1][0]);
			Theorem canonLeft = d_rules->canonMultConstConst(thm.getExpr()[0][0], thm.getExpr()[0][1]);


			thm = iffMP(thm, substitutivityRule(thm.getExpr(), canonLeft, canonRight));


			upperBounds.push_back(thm);
		}

		else {

			Theorem thm = getLowerBoundThm(x);


			thm = iffMP(thm, d_rules->multIneqn(thm.getExpr(), a));


			Theorem canonRight  = d_rules->canonMultTermConst(thm.getExpr()[1][1], thm.getExpr()[1][0]);
			Theorem canonLeft = d_rules->canonMultConstConst(thm.getExpr()[0][0], thm.getExpr()[0][1]);


			thm = iffMP(thm, substitutivityRule(thm.getExpr(), canonLeft, canonRight));


			upperBounds.push_back(thm);
		}
	}


	Theorem sumInequalities = upperBounds[0];
	for(unsigned int i = 1; i < upperBounds.size(); i ++) {

		sumInequalities = d_rules->addInequalities(sumInequalities, upperBounds[i]);


		Theorem canonLeft  = d_rules->canonPlus(sumInequalities.getExpr()[0]);
		Theorem canonRight = d_rules->canonPlus(sumInequalities.getExpr()[1]);


		sumInequalities = iffMP(sumInequalities, substitutivityRule(sumInequalities.getExpr(), canonLeft, canonRight));
	}


	Theorem varUpperBound = substitutivityRule(sumInequalities.getExpr(), 1, symmetryRule(tableauxTheorem));

	varUpperBound = iffMP(sumInequalities, varUpperBound);


	Theorem varLowerBound = getLowerBoundThm(var);


	return d_rules->clashingBounds(varLowerBound, varUpperBound);
}
