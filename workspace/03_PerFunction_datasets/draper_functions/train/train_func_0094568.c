getTableauxEntry(const Expr& x_i, const Expr& x_j) {
	return findCoefficient(x_j, tableaux[x_i].getExpr()[1]);
}
