advance_transition_function(AggState *aggstate,
							AggStatePerTrans pertrans,
							AggStatePerGroup pergroupstate)
{
	FunctionCallInfo fcinfo = &pertrans->transfn_fcinfo;
	MemoryContext oldContext;
	Datum		newVal;

	if (pertrans->transfn.fn_strict)
	{


		int			numTransInputs = pertrans->numTransInputs;
		int			i;

		for (i = 1; i <= numTransInputs; i++)
		{
			if (fcinfo->argnull[i])
				return;
		}
		if (pergroupstate->noTransValue)
		{


			oldContext = MemoryContextSwitchTo(
											   aggstate->aggcontexts[aggstate->current_set]->ecxt_per_tuple_memory);
			pergroupstate->transValue = datumCopy(fcinfo->arg[1],
												  pertrans->transtypeByVal,
												  pertrans->transtypeLen);
			pergroupstate->transValueIsNull = false;
			pergroupstate->noTransValue = false;
			MemoryContextSwitchTo(oldContext);
			return;
		}
		if (pergroupstate->transValueIsNull)
		{


			return;
		}
	}


	oldContext = MemoryContextSwitchTo(aggstate->tmpcontext->ecxt_per_tuple_memory);


	aggstate->curpertrans = pertrans;


	fcinfo->arg[0] = pergroupstate->transValue;
	fcinfo->argnull[0] = pergroupstate->transValueIsNull;
	fcinfo->isnull = false;

	newVal = FunctionCallInvoke(fcinfo);

	aggstate->curpertrans = NULL;


	if (!pertrans->transtypeByVal &&
		DatumGetPointer(newVal) != DatumGetPointer(pergroupstate->transValue))
	{
		if (!fcinfo->isnull)
		{
			MemoryContextSwitchTo(aggstate->aggcontexts[aggstate->current_set]->ecxt_per_tuple_memory);
			newVal = datumCopy(newVal,
							   pertrans->transtypeByVal,
							   pertrans->transtypeLen);
		}
		if (!pergroupstate->transValueIsNull)
			pfree(DatumGetPointer(pergroupstate->transValue));
	}

	pergroupstate->transValue = newVal;
	pergroupstate->transValueIsNull = fcinfo->isnull;

	MemoryContextSwitchTo(oldContext);
}
