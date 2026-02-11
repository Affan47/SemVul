ProcessQuery(PlannedStmt *plan,
			 const char *sourceText,
			 ParamListInfo params,
			 DestReceiver *dest,
			 char *completionTag)
{
	QueryDesc  *queryDesc;

	elog(DEBUG3, "ProcessQuery");


	queryDesc = CreateQueryDesc(plan, sourceText,
								GetActiveSnapshot(), InvalidSnapshot,
								dest, params, 0);


	ExecutorStart(queryDesc, 0);


	ExecutorRun(queryDesc, ForwardScanDirection, 0L);


	if (completionTag)
	{
		Oid			lastOid;

		switch (queryDesc->operation)
		{
			case CMD_SELECT:
				snprintf(completionTag, COMPLETION_TAG_BUFSIZE,
						 "SELECT %u", queryDesc->estate->es_processed);
				break;
			case CMD_INSERT:
				if (queryDesc->estate->es_processed == 1)
					lastOid = queryDesc->estate->es_lastoid;
				else
					lastOid = InvalidOid;
				snprintf(completionTag, COMPLETION_TAG_BUFSIZE,
				   "INSERT %u %u", lastOid, queryDesc->estate->es_processed);
				break;
			case CMD_UPDATE:
				snprintf(completionTag, COMPLETION_TAG_BUFSIZE,
						 "UPDATE %u", queryDesc->estate->es_processed);
				break;
			case CMD_DELETE:
				snprintf(completionTag, COMPLETION_TAG_BUFSIZE,
						 "DELETE %u", queryDesc->estate->es_processed);
				break;
			default:
				strcpy(completionTag, "???");
				break;
		}
	}


	ExecutorFinish(queryDesc);
	ExecutorEnd(queryDesc);

	FreeQueryDesc(queryDesc);
}
