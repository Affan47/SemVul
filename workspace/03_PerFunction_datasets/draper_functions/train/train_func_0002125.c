make_pathkey_from_sortinfo(PlannerInfo *root,
						   Expr *expr,
						   Oid opfamily,
						   Oid opcintype,
						   bool reverse_sort,
						   bool nulls_first,
						   Index sortref,
						   bool create_it,
						   bool canonicalize)
{
	int16		strategy;
	Oid			equality_op;
	List	   *opfamilies;
	EquivalenceClass *eclass;

	strategy = reverse_sort ? BTGreaterStrategyNumber : BTLessStrategyNumber;


	equality_op = get_opfamily_member(opfamily,
									  opcintype,
									  opcintype,
									  BTEqualStrategyNumber);
	if (!OidIsValid(equality_op))
		elog(ERROR, "could not find equality operator for opfamily %u",
			 opfamily);
	opfamilies = get_mergejoin_opfamilies(equality_op);
	if (!opfamilies)
		elog(ERROR, "could not find opfamilies for equality operator %u",
			 equality_op);


	if (exprType((Node *) expr) != opcintype &&
		!IsPolymorphicType(opcintype))
	{

		while (expr && IsA(expr, RelabelType))
			expr = (Expr *) ((RelabelType *) expr)->arg;
		if (exprType((Node *) expr) != opcintype)
			expr = (Expr *) makeRelabelType(expr,
											opcintype,
											-1,
											COERCE_DONTCARE);
	}


	eclass = get_eclass_for_sort_expr(root, expr, opcintype, opfamilies,
									  sortref, create_it);


	if (!eclass)
		return NULL;


	if (canonicalize)
		return make_canonical_pathkey(root, eclass, opfamily,
									  strategy, nulls_first);
	else
		return makePathKey(eclass, opfamily, strategy, nulls_first);
}
