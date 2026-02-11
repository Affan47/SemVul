_SPI_pquery(QueryDesc *queryDesc, bool fire_triggers, long tcount)
{
	int			operation = queryDesc->operation;
	int			eflags;
	int			res;

	switch (operation)
	{
		case CMD_SELECT:
			Assert(queryDesc->plannedstmt->utilityStmt == NULL);
			if (queryDesc->plannedstmt->intoClause)
				res = SPI_OK_SELINTO;
			else if (queryDesc->dest->mydest != DestSPI)
			{

				res = SPI_OK_UTILITY;
			}
			else
				res = SPI_OK_SELECT;
			break;
		case CMD_INSERT:
			if (queryDesc->plannedstmt->hasReturning)
				res = SPI_OK_INSERT_RETURNING;
			else
				res = SPI_OK_INSERT;
			break;
		case CMD_DELETE:
			if (queryDesc->plannedstmt->hasReturning)
				res = SPI_OK_DELETE_RETURNING;
			else
				res = SPI_OK_DELETE;
			break;
		case CMD_UPDATE:
			if (queryDesc->plannedstmt->hasReturning)
				res = SPI_OK_UPDATE_RETURNING;
			else
				res = SPI_OK_UPDATE;
			break;
		default:
			return SPI_ERROR_OPUNKNOWN;
	}

#ifdef SPI_EXECUTOR_STATS
	if (ShowExecutorStats)
		ResetUsage();
#endif


	if (fire_triggers)
		eflags = 0;
	else
		eflags = EXEC_FLAG_SKIP_TRIGGERS;

	ExecutorStart(queryDesc, eflags, 'r');

	ExecutorRun(queryDesc, ForwardScanDirection, tcount);

	_SPI_current->processed = queryDesc->estate->es_processed;
	_SPI_current->lastoid = queryDesc->estate->es_lastoid;

	if ((res == SPI_OK_SELECT || queryDesc->plannedstmt->hasReturning) &&
		queryDesc->dest->mydest == DestSPI)
	{
		if (_SPI_checktuples())
			elog(ERROR, "consistency check on SPI tuple count failed");
	}

	ExecutorFinish(queryDesc);
	ExecutorEnd(queryDesc);


#ifdef SPI_EXECUTOR_STATS
	if (ShowExecutorStats)
		ShowUsage("SPI EXECUTOR STATS");
#endif

	return res;
}
