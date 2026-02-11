advance_windowaggregate(WindowAggState *winstate,
						WindowStatePerFunc perfuncstate,
						WindowStatePerAgg peraggstate)
{
	WindowFuncExprState *wfuncstate = perfuncstate->wfuncstate;
	int			numArguments = perfuncstate->numArguments;
	FunctionCallInfoData fcinfodata;
	FunctionCallInfo fcinfo = &fcinfodata;
	Datum		newVal;
	ListCell   *arg;
	int			i;
	MemoryContext oldContext;
	ExprContext *econtext = winstate->tmpcontext;

	oldContext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);


	i = 1;
	foreach(arg, wfuncstate->args)
	{
		ExprState  *argstate = (ExprState *) lfirst(arg);

		fcinfo->arg[i] = ExecEvalExpr(argstate, econtext,
									  &fcinfo->argnull[i], NULL);
		i++;
	}

	if (peraggstate->transfn.fn_strict)
	{


		for (i = 1; i <= numArguments; i++)
		{
			if (fcinfo->argnull[i])
			{
				MemoryContextSwitchTo(oldContext);
				return;
			}
		}
		if (peraggstate->noTransValue)
		{


			MemoryContextSwitchTo(winstate->aggcontext);
			peraggstate->transValue = datumCopy(fcinfo->arg[1],
												peraggstate->transtypeByVal,
												peraggstate->transtypeLen);
			peraggstate->transValueIsNull = false;
			peraggstate->noTransValue = false;
			MemoryContextSwitchTo(oldContext);
			return;
		}
		if (peraggstate->transValueIsNull)
		{


			MemoryContextSwitchTo(oldContext);
			return;
		}
	}


	InitFunctionCallInfoData(*fcinfo, &(peraggstate->transfn),
							 numArguments + 1,
							 perfuncstate->winCollation,
							 (void *) winstate, NULL);
	fcinfo->arg[0] = peraggstate->transValue;
	fcinfo->argnull[0] = peraggstate->transValueIsNull;
	newVal = FunctionCallInvoke(fcinfo);


	if (!peraggstate->transtypeByVal &&
		DatumGetPointer(newVal) != DatumGetPointer(peraggstate->transValue))
	{
		if (!fcinfo->isnull)
		{
			MemoryContextSwitchTo(winstate->aggcontext);
			newVal = datumCopy(newVal,
							   peraggstate->transtypeByVal,
							   peraggstate->transtypeLen);
		}
		if (!peraggstate->transValueIsNull)
			pfree(DatumGetPointer(peraggstate->transValue));
	}

	MemoryContextSwitchTo(oldContext);
	peraggstate->transValue = newVal;
	peraggstate->transValueIsNull = fcinfo->isnull;
}
