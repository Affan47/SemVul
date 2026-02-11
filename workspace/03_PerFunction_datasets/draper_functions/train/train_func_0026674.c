match_rowcompare_to_indexcol(IndexOptInfo *index,
							 int indexcol,
							 Oid opfamily,
							 Oid idxcollation,
							 RowCompareExpr *clause)
{
	Index		index_relid = index->rel->relid;
	Node	   *leftop,
			   *rightop;
	Oid			expr_op;
	Oid			expr_coll;


	if (index->relam != BTREE_AM_OID)
		return false;


	leftop = (Node *) linitial(clause->largs);
	rightop = (Node *) linitial(clause->rargs);
	expr_op = linitial_oid(clause->opnos);
	expr_coll = linitial_oid(clause->inputcollids);


	if (!IndexCollMatchesExprColl(idxcollation, expr_coll))
		return false;


	if (match_index_to_operand(leftop, indexcol, index) &&
		!bms_is_member(index_relid, pull_varnos(rightop)) &&
		!contain_volatile_functions(rightop))
	{

	}
	else if (match_index_to_operand(rightop, indexcol, index) &&
			 !bms_is_member(index_relid, pull_varnos(leftop)) &&
			 !contain_volatile_functions(leftop))
	{

		expr_op = get_commutator(expr_op);
		if (expr_op == InvalidOid)
			return false;
	}
	else
		return false;


	switch (get_op_opfamily_strategy(expr_op, opfamily))
	{
		case BTLessStrategyNumber:
		case BTLessEqualStrategyNumber:
		case BTGreaterEqualStrategyNumber:
		case BTGreaterStrategyNumber:
			return true;
	}

	return false;
}
