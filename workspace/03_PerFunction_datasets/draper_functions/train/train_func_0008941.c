EvalPlanQualEnd(EPQState *epqstate)
{
	EState	   *estate = epqstate->estate;
	MemoryContext oldcontext;
	ListCell   *l;

	if (estate == NULL)
		return;

	oldcontext = MemoryContextSwitchTo(estate->es_query_cxt);

	ExecEndNode(epqstate->planstate);

	foreach(l, estate->es_subplanstates)
	{
		PlanState  *subplanstate = (PlanState *) lfirst(l);

		ExecEndNode(subplanstate);
	}


	ExecResetTupleTable(estate->es_tupleTable, false);


	foreach(l, estate->es_trig_target_relations)
	{
		ResultRelInfo *resultRelInfo = (ResultRelInfo *) lfirst(l);


		ExecCloseIndices(resultRelInfo);
		heap_close(resultRelInfo->ri_RelationDesc, NoLock);
	}

	MemoryContextSwitchTo(oldcontext);

	FreeExecutorState(estate);


	epqstate->estate = NULL;
	epqstate->planstate = NULL;
	epqstate->origslot = NULL;
}
