GetGTerms2(set<Expr>& formula_map, set<Expr>& G_terms) {

	for (set<Expr>::iterator i = formula_map.begin(); i != formula_map.end(); i++)
		if ((*i)[0].isTerm())
			for (int j = 0; j < 2; j++)  {
				 G_terms.insert((*i)[j]);
			}
}
