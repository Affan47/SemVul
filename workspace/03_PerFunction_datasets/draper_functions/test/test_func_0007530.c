init_execution_state(List *queryTree_list,
					 SQLFunctionCachePtr fcache,
					 bool lazyEvalOK)
{
	execution_state *firstes = NULL;
	execution_state *preves = NULL;
	execution_state *lasttages = NULL;
	ListCell   *qtl_item;

	foreach(qtl_item, queryTree_list)
	{
		Query	   *queryTree = (Query *) lfirst(qtl_item);
		Node	   *stmt;
		execution_state *newes;

		Assert(IsA(queryTree, Query));

		if (queryTree->commandType == CMD_UTILITY)
			stmt = queryTree->utilityStmt;
		else
			stmt = (Node *) pg_plan_query(queryTree, 0, NULL);


		if (IsA(stmt, TransactionStmt))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),

					 errmsg("%s is not allowed in a SQL function",
							CreateCommandTag(stmt))));

		if (fcache->readonly_func && !CommandIsReadOnly(stmt))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),

					 errmsg("%s is not allowed in a non-volatile function",
							CreateCommandTag(stmt))));

		newes = (execution_state *) palloc(sizeof(execution_state));
		if (preves)
			preves->next = newes;
		else
			firstes = newes;

		newes->next = NULL;
		newes->status = F_EXEC_START;
		newes->setsResult = false;
		newes->lazyEval = false;
		newes->stmt = stmt;
		newes->qd = NULL;

		if (queryTree->canSetTag)
			lasttages = newes;

		preves = newes;
	}


	if (lasttages && fcache->junkFilter)
	{
		lasttages->setsResult = true;
		if (lazyEvalOK &&
			IsA(lasttages->stmt, PlannedStmt))
		{
			PlannedStmt *ps = (PlannedStmt *) lasttages->stmt;

			if (ps->commandType == CMD_SELECT &&
				ps->utilityStmt == NULL &&
				ps->intoClause == NULL)
				fcache->lazyEval = lasttages->lazyEval = true;
		}
	}

	return firstes;
}
