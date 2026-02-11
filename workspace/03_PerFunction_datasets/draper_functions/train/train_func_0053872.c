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
	else if (IsA(node, OpExpr))
	{
		OpExpr	   *expr = (OpExpr *) node;

		set_opfuncid(expr);
		if (func_volatile(expr->opfuncid) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	else if (IsA(node, DistinctExpr))
	{
		DistinctExpr *expr = (DistinctExpr *) node;

		set_opfuncid((OpExpr *) expr);
		if (func_volatile(expr->opfuncid) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	else if (IsA(node, NullIfExpr))
	{
		NullIfExpr *expr = (NullIfExpr *) node;

		set_opfuncid((OpExpr *) expr);
		if (func_volatile(expr->opfuncid) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	else if (IsA(node, ScalarArrayOpExpr))
	{
		ScalarArrayOpExpr *expr = (ScalarArrayOpExpr *) node;

		set_sa_opfuncid(expr);
		if (func_volatile(expr->opfuncid) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	else if (IsA(node, CoerceViaIO))
	{
		CoerceViaIO *expr = (CoerceViaIO *) node;
		Oid			iofunc;
		Oid			typioparam;
		bool		typisvarlena;


		getTypeInputInfo(expr->resulttype,
						 &iofunc, &typioparam);
		if (func_volatile(iofunc) != PROVOLATILE_IMMUTABLE)
			return true;

		getTypeOutputInfo(exprType((Node *) expr->arg),
						  &iofunc, &typisvarlena);
		if (func_volatile(iofunc) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	else if (IsA(node, ArrayCoerceExpr))
	{
		ArrayCoerceExpr *expr = (ArrayCoerceExpr *) node;

		if (OidIsValid(expr->elemfuncid) &&
			func_volatile(expr->elemfuncid) != PROVOLATILE_IMMUTABLE)
			return true;

	}
	else if (IsA(node, RowCompareExpr))
	{
		RowCompareExpr *rcexpr = (RowCompareExpr *) node;
		ListCell   *opid;

		foreach(opid, rcexpr->opnos)
		{
			if (op_volatile(lfirst_oid(opid)) != PROVOLATILE_IMMUTABLE)
				return true;
		}

	}
	else if (IsA(node, Query))
	{

		return query_tree_walker((Query *) node,
								 contain_mutable_functions_walker,
								 context, 0);
	}
	return expression_tree_walker(node, contain_mutable_functions_walker,
								  context);
}
