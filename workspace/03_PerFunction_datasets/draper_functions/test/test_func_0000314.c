postquel_get_single_result(TupleTableSlot *slot,
						   FunctionCallInfo fcinfo,
						   SQLFunctionCachePtr fcache,
						   MemoryContext resultcontext)
{
	Datum		value;
	MemoryContext oldcontext;


	oldcontext = MemoryContextSwitchTo(resultcontext);

	if (fcache->returnsTuple)
	{

		fcinfo->isnull = false;
		value = ExecFetchSlotTupleDatum(slot);
		value = datumCopy(value, fcache->typbyval, fcache->typlen);
	}
	else
	{


		value = slot_getattr(slot, 1, &(fcinfo->isnull));

		if (!fcinfo->isnull)
			value = datumCopy(value, fcache->typbyval, fcache->typlen);
	}

	MemoryContextSwitchTo(oldcontext);

	return value;
}
