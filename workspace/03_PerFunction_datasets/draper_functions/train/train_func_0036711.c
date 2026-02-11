update(const Expr& x_i, const EpsRational& v) {


	DebugAssert(tableaux.find(x_i) == tableaux.end(), "TheoryArithNew::update, given variable should be non-basic" + x_i.toString());


	TRACE("simplex", "TheoryArithNew::update(", x_i.toString() + ", " + v.toString(), ")");


	EpsRational old_value = getBeta(x_i);


	DependenciesMap::iterator find = dependenciesMap.find(x_i);
	if (find != dependenciesMap.end()) {


		const set<Expr>& dependent = (*find).second;
		set<Expr>::const_iterator it     = dependent.begin();
		set<Expr>::const_iterator it_end = dependent.end();

		while (it != it_end) {


			const Expr& x_j = *it;


			const Rational& a_ji = getTableauxEntry(x_j, x_i);


			EpsRational b(getBeta(x_j));
			EpsRational x_j_new = beta[x_j] = b + (v - old_value) * a_ji;


			if (x_j_new < getLowerBound(x_j) || getUpperBound(x_j) < x_j_new)
				unsatBasicVariables.insert(x_j);
			else
				unsatBasicVariables.erase(x_j);


			it ++;
		}
	}


	beta[x_i] = v;
}
