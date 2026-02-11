finalize_aggregate(AggState *aggstate,
				   AggStatePerAgg peragg,
				   AggStatePerGroup pergroupstate,
				   Datum *resultVal, bool *resultIsNull)
{
	FunctionCallInfoData fcinfo;
	bool		anynull = false;
	MemoryContext oldContext;
	int			i;
	ListCell   *lc;
	AggStatePerTrans pertrans = &aggstate->pertrans[peragg->transno];

	oldContext = MemoryContextSwitchTo(aggstate->ss.ps.ps_ExprContext->ecxt_per_tuple_memory);


	i = 1;
	foreach(lc, pertrans->aggdirectargs)
	{
		ExprState  *expr = (ExprState *) lfirst(lc);

		fcinfo.arg[i] = ExecEvalExpr(expr,
									 aggstate->ss.ps.ps_ExprContext,
									 &fcinfo.argnull[i],
									 NULL);
		anynull |= fcinfo.argnull[i];
		i++;
	}


	if (OidIsValid(peragg->finalfn_oid))
	{
		int			numFinalArgs = peragg->numFinalArgs;


		aggstate->curpertrans = pertrans;

		InitFunctionCallInfoData(fcinfo, &peragg->finalfn,
								 numFinalArgs,
								 pertrans->aggCollation,
								 (void *) aggstate, NULL);


		fcinfo.arg[0] = pergroupstate->transValue;
		fcinfo.argnull[0] = pergroupstate->transValueIsNull;
		anynull |= pergroupstate->transValueIsNull;


		for (; i < numFinalArgs; i++)
		{
			fcinfo.arg[i] = (Datum) 0;
			fcinfo.argnull[i] = true;
			anynull = true;
		}

		if (fcinfo.flinfo->fn_strict && anynull)
		{

			*resultVal = (Datum) 0;
			*resultIsNull = true;
		}
		else
		{
			*resultVal = FunctionCallInvoke(&fcinfo);
			*resultIsNull = fcinfo.isnull;
		}
		aggstate->curpertrans = NULL;
	}
	else
	{
		*resultVal = pergroupstate->transValue;
		*resultIsNull = pergroupstate->transValueIsNull;
	}


	if (!peragg->resulttypeByVal && !*resultIsNull &&
		!MemoryContextContains(CurrentMemoryContext,
							   DatumGetPointer(*resultVal)))
		*resultVal = datumCopy(*resultVal,
							   peragg->resulttypeByVal,
							   peragg->resulttypeLen);

	MemoryContextSwitchTo(oldContext);
}
