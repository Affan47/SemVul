ExecuteQuery(ExecuteStmt *stmt, const char *queryString,
			 ParamListInfo params,
			 DestReceiver *dest, char *completionTag)
{
	PreparedStatement *entry;
	CachedPlan *cplan;
	List	   *plan_list;
	ParamListInfo paramLI = NULL;
	EState	   *estate = NULL;
	Portal		portal;
	char	   *query_string;


	entry = FetchPreparedStatement(stmt->name, true);


	if (!entry->plansource->fully_planned)
		elog(ERROR, "EXECUTE does not support unplanned prepared statements");

	if (!entry->plansource->fixed_result)
		elog(ERROR, "EXECUTE does not support variable-result cached plans");


	if (entry->plansource->num_params > 0)
	{


		estate = CreateExecutorState();
		estate->es_param_list_info = params;
		paramLI = EvaluateParams(entry, stmt->params,
								 queryString, estate);
	}


	portal = CreateNewPortal();

	portal->visible = false;


	query_string = MemoryContextStrdup(PortalGetHeapMemory(portal),
									   entry->plansource->query_string);


	if (stmt->into)
	{
		MemoryContext oldContext;
		PlannedStmt *pstmt;


		cplan = RevalidateCachedPlan(entry->plansource, true);


		oldContext = MemoryContextSwitchTo(PortalGetHeapMemory(portal));

		plan_list = copyObject(cplan->stmt_list);

		if (list_length(plan_list) != 1)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("prepared statement is not a SELECT")));
		pstmt = (PlannedStmt *) linitial(plan_list);
		if (!IsA(pstmt, PlannedStmt) ||
			pstmt->commandType != CMD_SELECT ||
			pstmt->utilityStmt != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("prepared statement is not a SELECT")));
		pstmt->intoClause = copyObject(stmt->into);

		MemoryContextSwitchTo(oldContext);


		ReleaseCachedPlan(cplan, true);

		cplan = NULL;
	}
	else
	{

		cplan = RevalidateCachedPlan(entry->plansource, false);
		plan_list = cplan->stmt_list;
	}

	PortalDefineQuery(portal,
					  NULL,
					  query_string,
					  entry->plansource->commandTag,
					  plan_list,
					  cplan);


	PortalStart(portal, paramLI, GetActiveSnapshot());

	(void) PortalRun(portal, FETCH_ALL, false, dest, dest, completionTag);

	PortalDrop(portal, false);

	if (estate)
		FreeExecutorState(estate);


}
