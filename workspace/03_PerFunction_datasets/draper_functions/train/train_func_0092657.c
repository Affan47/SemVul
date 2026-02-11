contain_mutable_functions_walker(Node *node, void *context)
{
	if (node == NULL)
		return false;
	if (IsA(node, FuncExpr))
	{
		FuncExpr   *expr = (FuncExpr *) node;

		if (func_volatile(expr->funcid) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	if (IsA(node, OpExpr))
	{
		OpExpr	   *expr = (OpExpr *) node;

		if (op_volatile(expr->opno) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	if (IsA(node, DistinctExpr))
	{
		DistinctExpr *expr = (DistinctExpr *) node;

		if (op_volatile(expr->opno) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	if (IsA(node, ScalarArrayOpExpr))
	{
		ScalarArrayOpExpr *expr = (ScalarArrayOpExpr *) node;

		if (op_volatile(expr->opno) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	if (IsA(node, NullIfExpr))
	{
		NullIfExpr *expr = (NullIfExpr *) node;

		if (op_volatile(expr->opno) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	if (IsA(node, RowCompareExpr))
	{
		RowCompareExpr *rcexpr = (RowCompareExpr *) node;
		ListCell   *opid;

		foreach(opid, rcexpr->opnos)
		{
			if (op_volatile(lfirst_oid(opid)) != PROVOLATILE_IMMUTABLE)
				return true;
		}

	}
	return expression_tree_walker(node, contain_mutable_functions_walker,
								  context);
}
