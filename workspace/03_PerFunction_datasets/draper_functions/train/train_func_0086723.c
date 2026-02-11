RemoveFunctionApps(const Expr& orig, set<Expr>& Not_replaced_set, vector<Expr>& Old, vector<Expr>& New, T_ITE_map& ITE_map, set<Expr>& SeenBefore) {
	if (!SeenBefore.insert( orig ).second)
		return;

	for (int i = 0; i < orig.arity() ; i++)
		RemoveFunctionApps(orig[i], Not_replaced_set, Old, New, ITE_map, SeenBefore);
    if (orig.isApply() && orig.getOpKind() == UFUNC && Not_replaced_set.find(orig) != Not_replaced_set.end()) {
		Old.push_back(orig);
		New.push_back(ITE_map.find(orig)->second);
	}
}
