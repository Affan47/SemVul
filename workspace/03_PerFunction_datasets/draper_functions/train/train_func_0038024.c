ExplainExecuteQuery(ExecuteStmt *execstmt, ExplainState *es,
					const char *queryString, ParamListInfo params)
{
	PreparedStatement *entry;
	const char *query_string;
	CachedPlan *cplan;
	List	   *plan_list;
	ListCell   *p;
	ParamListInfo paramLI = NULL;
	EState	   *estate = NULL;


	entry = FetchPreparedStatement(execstmt->name, true);


	if (!entry->plansource->fully_planned)
		elog(ERROR, "EXPLAIN EXECUTE does not support unplanned prepared statements");

	if (!entry->plansource->fixed_result)
		elog(ERROR, "EXPLAIN EXECUTE does not support variable-result cached plans");

	query_string = entry->plansource->query_string;


	cplan = RevalidateCachedPlan(entry->plansource, true);

	plan_list = cplan->stmt_list;


	if (entry->plansource->num_params)
	{


		estate = CreateExecutorState();
		estate->es_param_list_info = params;
		paramLI = EvaluateParams(entry, execstmt->params,
								 queryString, estate);
	}


	foreach(p, plan_list)
	{
		PlannedStmt *pstmt = (PlannedStmt *) lfirst(p);

		if (IsA(pstmt, PlannedStmt))
		{
			if (execstmt->into)
			{
				if (pstmt->commandType != CMD_SELECT ||
					pstmt->utilityStmt != NULL)
					ereport(ERROR,
							(errcode(ERRCODE_WRONG_OBJECT_TYPE),
							 errmsg("prepared statement is not a SELECT")));


				pstmt = copyObject(pstmt);

				pstmt->intoClause = execstmt->into;
			}

			ExplainOnePlan(pstmt, es, query_string, paramLI);
		}
		else
		{
			ExplainOneUtility((Node *) pstmt, es, query_string, params);
		}


		if (lnext(p) != NULL)
			ExplainSeparatePlans(es);
	}

	if (estate)
		FreeExecutorState(estate);

	ReleaseCachedPlan(cplan, true);
}
