make_pathkey_from_sortop(PlannerInfo *root,
						 Expr *expr,
						 Oid ordering_op,
						 bool nulls_first,
						 Index sortref,
						 bool create_it,
						 bool canonicalize)
{
	Oid			opfamily,
				opcintype,
				collation;
	int16		strategy;


	if (!get_ordering_op_properties(ordering_op,
									&opfamily, &opcintype, &strategy))
		elog(ERROR, "operator %u is not a valid ordering operator",
			 ordering_op);


	collation = exprCollation((Node *) expr);

	return make_pathkey_from_sortinfo(root,
									  expr,
									  opfamily,
									  opcintype,
									  collation,
									  (strategy == BTGreaterStrategyNumber),
									  nulls_first,
									  sortref,
									  create_it,
									  canonicalize);
}
