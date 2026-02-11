postquel_start(execution_state *es, SQLFunctionCachePtr fcache)
{
	Snapshot	snapshot;

	Assert(es->qd == NULL);


	if (fcache->readonly_func)
		snapshot = CopySnapshot(ActiveSnapshot);
	else
	{
		CommandCounterIncrement();
		snapshot = CopySnapshot(GetTransactionSnapshot());
	}

	es->qd = CreateQueryDesc(es->query, es->plan,
							 snapshot, InvalidSnapshot,
							 None_Receiver,
							 fcache->paramLI, false);


	if (es->qd->operation != CMD_UTILITY)
	{


		if (es->qd->operation != CMD_SELECT)
			AfterTriggerBeginQuery();
		ExecutorStart(es->qd, 0);
	}

	es->status = F_EXEC_RUN;
}
