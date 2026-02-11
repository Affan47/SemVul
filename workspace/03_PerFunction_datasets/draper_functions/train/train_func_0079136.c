simplify_EXISTS_query(PlannerInfo *root, Query *query)
{


	if (query->commandType != CMD_SELECT ||
		query->setOperations ||
		query->hasAggs ||
		query->groupingSets ||
		query->hasWindowFuncs ||
		query->hasModifyingCTE ||
		query->havingQual ||
		query->limitOffset ||
		query->rowMarks)
		return false;


	if (query->limitCount)
	{


		Node	   *node = eval_const_expressions(root, query->limitCount);
		Const	   *limit;


		query->limitCount = node;

		if (!IsA(node, Const))
			return false;

		limit = (Const *) node;
		Assert(limit->consttype == INT8OID);
		if (!limit->constisnull && DatumGetInt64(limit->constvalue) <= 0)
			return false;


		query->limitCount = NULL;
	}


	if (expression_returns_set((Node *) query->targetList))
		return false;


	query->targetList = NIL;
	query->groupClause = NIL;
	query->windowClause = NIL;
	query->distinctClause = NIL;
	query->sortClause = NIL;
	query->hasDistinctOn = false;

	return true;
}
