standard_ExecutorRun(QueryDesc *queryDesc,
					 ScanDirection direction, long count)
{
	EState	   *estate;
	CmdType		operation;
	DestReceiver *dest;
	bool		sendTuples;
	MemoryContext oldcontext;


	Assert(queryDesc != NULL);

	estate = queryDesc->estate;

	Assert(estate != NULL);


	oldcontext = MemoryContextSwitchTo(estate->es_query_cxt);


	if (queryDesc->totaltime)
		InstrStartNode(queryDesc->totaltime);


	operation = queryDesc->operation;
	dest = queryDesc->dest;


	estate->es_processed = 0;
	estate->es_lastoid = InvalidOid;

	sendTuples = (operation == CMD_SELECT ||
				  queryDesc->plannedstmt->returningLists);

	if (sendTuples)
		(*dest->rStartup) (dest, operation, queryDesc->tupDesc);


	if (!ScanDirectionIsNoMovement(direction))
		ExecutePlan(estate,
					queryDesc->planstate,
					operation,
					count,
					direction,
					dest);


	if (sendTuples)
		(*dest->rShutdown) (dest);

	if (queryDesc->totaltime)
		InstrStopNode(queryDesc->totaltime, estate->es_processed);

	MemoryContextSwitchTo(oldcontext);
}
