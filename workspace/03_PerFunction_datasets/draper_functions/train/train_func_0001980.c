ShutdownSQLFunction(Datum arg)
{
	SQLFunctionCachePtr fcache = (SQLFunctionCachePtr) DatumGetPointer(arg);
	execution_state *es;
	ListCell   *lc;

	foreach(lc, fcache->func_state)
	{
		es = (execution_state *) lfirst(lc);
		while (es)
		{

			if (es->status == F_EXEC_RUN)
			{

				if (!fcache->readonly_func)
					PushActiveSnapshot(es->qd->snapshot);

				postquel_end(es);

				if (!fcache->readonly_func)
					PopActiveSnapshot();
			}


			es->status = F_EXEC_START;
			es = es->next;
		}
	}


	if (fcache->tstore)
		tuplestore_end(fcache->tstore);
	fcache->tstore = NULL;


	fcache->shutdown_reg = false;
}
