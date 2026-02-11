standard_ExecutorEnd(QueryDesc *queryDesc)
{
	EState	   *estate;
	MemoryContext oldcontext;


	Assert(queryDesc != NULL);

	estate = queryDesc->estate;

	Assert(estate != NULL);


	Assert(estate->es_finished ||
		   (estate->es_top_eflags & EXEC_FLAG_EXPLAIN_ONLY));


	oldcontext = MemoryContextSwitchTo(estate->es_query_cxt);

	ExecEndPlan(queryDesc->planstate, estate);


	UnregisterSnapshot(estate->es_snapshot);
	UnregisterSnapshot(estate->es_crosscheck_snapshot);


	MemoryContextSwitchTo(oldcontext);


	if (queryDesc->plannedstmt->parallelModeNeeded &&
		!(estate->es_top_eflags & EXEC_FLAG_EXPLAIN_ONLY))
		ExitParallelMode();


	FreeExecutorState(estate);


	queryDesc->tupDesc = NULL;
	queryDesc->estate = NULL;
	queryDesc->planstate = NULL;
	queryDesc->totaltime = NULL;
}
