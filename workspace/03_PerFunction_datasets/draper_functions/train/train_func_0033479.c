make_op(ParseState *pstate, List *opname, Node *ltree, Node *rtree,
		int location)
{
	Oid			ltypeId,
				rtypeId;
	Operator	tup;
	Expr	   *result;


	if (rtree == NULL)
	{

		ltypeId = exprType(ltree);
		rtypeId = InvalidOid;
		tup = right_oper(pstate, opname, ltypeId, false, location);
	}
	else if (ltree == NULL)
	{

		rtypeId = exprType(rtree);
		ltypeId = InvalidOid;
		tup = left_oper(pstate, opname, rtypeId, false, location);
	}
	else
	{

		ltypeId = exprType(ltree);
		rtypeId = exprType(rtree);
		tup = oper(pstate, opname, ltypeId, rtypeId, false, location);
	}


	result = make_op_expr(pstate, tup, ltree, rtree, ltypeId, rtypeId);

	ReleaseSysCache(tup);

	return result;
}
