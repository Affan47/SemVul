update_frameheadpos(WindowObject winobj, TupleTableSlot *slot)
{
	WindowAggState *winstate = winobj->winstate;
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	int			frameOptions = winstate->frameOptions;

	if (winstate->framehead_valid)
		return;

	if (frameOptions & FRAMEOPTION_START_UNBOUNDED_PRECEDING)
	{

		winstate->frameheadpos = 0;
		winstate->framehead_valid = true;
	}
	else if (frameOptions & FRAMEOPTION_START_CURRENT_ROW)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{

			winstate->frameheadpos = winstate->currentpos;
			winstate->framehead_valid = true;
		}
		else if (frameOptions & FRAMEOPTION_RANGE)
		{
			int64		fhprev;


			if (node->ordNumCols == 0)
			{
				winstate->frameheadpos = 0;
				winstate->framehead_valid = true;
				return;
			}


			fhprev = winstate->currentpos - 1;
			for (;;)
			{

				if (fhprev < winstate->frameheadpos)
					break;
				if (!window_gettupleslot(winobj, fhprev, slot))
					break;
				if (!are_peers(winstate, slot, winstate->ss.ss_ScanTupleSlot))
					break;
				fhprev--;
			}
			winstate->frameheadpos = fhprev + 1;
			winstate->framehead_valid = true;
		}
		else
			Assert(false);
	}
	else if (frameOptions & FRAMEOPTION_START_VALUE)
	{
		if (frameOptions & FRAMEOPTION_ROWS)
		{

			int64		offset = DatumGetInt64(winstate->startOffsetValue);

			if (frameOptions & FRAMEOPTION_START_VALUE_PRECEDING)
				offset = -offset;

			winstate->frameheadpos = winstate->currentpos + offset;

			if (winstate->frameheadpos < 0)
				winstate->frameheadpos = 0;
			else if (winstate->frameheadpos > winstate->currentpos)
			{

				spool_tuples(winstate, winstate->frameheadpos - 1);
				if (winstate->frameheadpos > winstate->spooled_rows)
					winstate->frameheadpos = winstate->spooled_rows;
			}
			winstate->framehead_valid = true;
		}
		else if (frameOptions & FRAMEOPTION_RANGE)
		{

			elog(ERROR, "window frame with value offset is not implemented");
		}
		else
			Assert(false);
	}
	else
		Assert(false);
}
