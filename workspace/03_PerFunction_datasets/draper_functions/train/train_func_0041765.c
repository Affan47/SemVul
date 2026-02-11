window_gettupleslot(WindowObject winobj, int64 pos, TupleTableSlot *slot)
{
	WindowAggState *winstate = winobj->winstate;
	MemoryContext oldcontext;


	if (pos < 0)
		return false;


	spool_tuples(winstate, pos);

	if (pos >= winstate->spooled_rows)
		return false;

	if (pos < winobj->markpos)
		elog(ERROR, "cannot fetch row before WindowObject's mark position");

	oldcontext = MemoryContextSwitchTo(winstate->ss.ps.ps_ExprContext->ecxt_per_query_memory);

	tuplestore_select_read_pointer(winstate->buffer, winobj->readptr);


	if (winobj->seekpos == pos)
	{
		tuplestore_advance(winstate->buffer, true);
		winobj->seekpos++;
	}

	while (winobj->seekpos > pos)
	{
		if (!tuplestore_gettupleslot(winstate->buffer, false, true, slot))
			elog(ERROR, "unexpected end of tuplestore");
		winobj->seekpos--;
	}

	while (winobj->seekpos < pos)
	{
		if (!tuplestore_gettupleslot(winstate->buffer, true, true, slot))
			elog(ERROR, "unexpected end of tuplestore");
		winobj->seekpos++;
	}

	MemoryContextSwitchTo(oldcontext);

	return true;
}
