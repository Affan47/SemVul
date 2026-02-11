ExecWindowAgg(WindowAggState *winstate)
{
	TupleTableSlot *result;
	ExprDoneCond isDone;
	ExprContext *econtext;
	int			i;
	int			numfuncs;

	if (winstate->all_done)
		return NULL;


	if (winstate->ss.ps.ps_TupFromTlist)
	{
		TupleTableSlot *result;
		ExprDoneCond isDone;

		result = ExecProject(winstate->ss.ps.ps_ProjInfo, &isDone);
		if (isDone == ExprMultipleResult)
			return result;

		winstate->ss.ps.ps_TupFromTlist = false;
	}

restart:
	if (winstate->buffer == NULL)
	{

		begin_partition(winstate);

	}
	else
	{

		winstate->currentpos++;

		winstate->frametail_valid = false;
	}


	spool_tuples(winstate, winstate->currentpos);


	if (winstate->partition_spooled &&
		winstate->currentpos >= winstate->spooled_rows)
	{
		release_partition(winstate);

		if (winstate->more_partitions)
		{
			begin_partition(winstate);
			Assert(winstate->spooled_rows > 0);
		}
		else
		{
			winstate->all_done = true;
			return NULL;
		}
	}


	econtext = winstate->ss.ps.ps_ExprContext;


	ResetExprContext(econtext);


	tuplestore_select_read_pointer(winstate->buffer, winstate->current_ptr);
	if (!tuplestore_gettupleslot(winstate->buffer, true, true,
								 winstate->ss.ss_ScanTupleSlot))
		elog(ERROR, "unexpected end of tuplestore");


	numfuncs = winstate->numfuncs;
	for (i = 0; i < numfuncs; i++)
	{
		WindowStatePerFunc perfuncstate = &(winstate->perfunc[i]);

		if (perfuncstate->plain_agg)
			continue;
		eval_windowfunction(winstate, perfuncstate,
			  &(econtext->ecxt_aggvalues[perfuncstate->wfuncstate->wfuncno]),
			  &(econtext->ecxt_aggnulls[perfuncstate->wfuncstate->wfuncno]));
	}


	if (winstate->numaggs > 0)
		eval_windowaggregates(winstate);


	tuplestore_trim(winstate->buffer);


	econtext->ecxt_outertuple = winstate->ss.ss_ScanTupleSlot;
	result = ExecProject(winstate->ss.ps.ps_ProjInfo, &isDone);

	if (isDone == ExprEndResult)
	{

		goto restart;
	}

	winstate->ss.ps.ps_TupFromTlist =
		(isDone == ExprMultipleResult);
	return result;
}
