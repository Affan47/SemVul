count_agg_clauses_walker(Node *node, AggClauseCounts *counts)
{
	if (node == NULL)
		return false;
	if (IsA(node, Aggref))
	{
		Aggref	   *aggref = (Aggref *) node;
		Oid		   *inputTypes;
		int			numArguments;
		HeapTuple	aggTuple;
		Form_pg_aggregate aggform;
		Oid			aggtranstype;
		int			i;
		ListCell   *l;

		Assert(aggref->agglevelsup == 0);
		counts->numAggs++;
		if (aggref->aggdistinct)
			counts->numDistinctAggs++;


		numArguments = list_length(aggref->args);
		inputTypes = (Oid *) palloc(sizeof(Oid) * numArguments);
		i = 0;
		foreach(l, aggref->args)
		{
			inputTypes[i++] = exprType((Node *) lfirst(l));
		}


		aggTuple = SearchSysCache(AGGFNOID,
								  ObjectIdGetDatum(aggref->aggfnoid),
								  0, 0, 0);
		if (!HeapTupleIsValid(aggTuple))
			elog(ERROR, "cache lookup failed for aggregate %u",
				 aggref->aggfnoid);
		aggform = (Form_pg_aggregate) GETSTRUCT(aggTuple);
		aggtranstype = aggform->aggtranstype;
		ReleaseSysCache(aggTuple);


		if (IsPolymorphicType(aggtranstype))
		{

			Oid		   *declaredArgTypes;
			int			agg_nargs;

			(void) get_func_signature(aggref->aggfnoid,
									  &declaredArgTypes, &agg_nargs);
			Assert(agg_nargs == numArguments);
			aggtranstype = enforce_generic_type_consistency(inputTypes,
															declaredArgTypes,
															agg_nargs,
															aggtranstype,
															false);
			pfree(declaredArgTypes);
		}


		if (!get_typbyval(aggtranstype))
		{
			int32		aggtranstypmod;
			int32		avgwidth;


			if (numArguments > 0 && aggtranstype == inputTypes[0])
				aggtranstypmod = exprTypmod((Node *) linitial(aggref->args));
			else
				aggtranstypmod = -1;

			avgwidth = get_typavgwidth(aggtranstype, aggtranstypmod);
			avgwidth = MAXALIGN(avgwidth);

			counts->transitionSpace += avgwidth + 2 * sizeof(void *);
		}
		else if (aggtranstype == INTERNALOID)
		{


			counts->transitionSpace += ALLOCSET_DEFAULT_INITSIZE;
		}


		if (contain_agg_clause((Node *) aggref->args))
			ereport(ERROR,
					(errcode(ERRCODE_GROUPING_ERROR),
					 errmsg("aggregate function calls cannot be nested")));


		return false;
	}
	Assert(!IsA(node, SubLink));
	return expression_tree_walker(node, count_agg_clauses_walker,
								  (void *) counts);
}
