accumArrayResult(ArrayBuildState *astate,
				 Datum dvalue, bool disnull,
				 Oid element_type,
				 MemoryContext rcontext)
{
	MemoryContext arr_context,
				oldcontext;

	if (astate == NULL)
	{


		arr_context = AllocSetContextCreate(rcontext,
											"accumArrayResult",
											ALLOCSET_DEFAULT_MINSIZE,
											ALLOCSET_DEFAULT_INITSIZE,
											ALLOCSET_DEFAULT_MAXSIZE);
		oldcontext = MemoryContextSwitchTo(arr_context);
		astate = (ArrayBuildState *) palloc(sizeof(ArrayBuildState));
		astate->mcontext = arr_context;
		astate->alen = 64;
		astate->dvalues = (Datum *) palloc(astate->alen * sizeof(Datum));
		astate->dnulls = (bool *) palloc(astate->alen * sizeof(bool));
		astate->nelems = 0;
		astate->element_type = element_type;
		get_typlenbyvalalign(element_type,
							 &astate->typlen,
							 &astate->typbyval,
							 &astate->typalign);
	}
	else
	{
		oldcontext = MemoryContextSwitchTo(astate->mcontext);
		Assert(astate->element_type == element_type);

		if (astate->nelems >= astate->alen)
		{
			astate->alen *= 2;
			astate->dvalues = (Datum *)
				repalloc(astate->dvalues, astate->alen * sizeof(Datum));
			astate->dnulls = (bool *)
				repalloc(astate->dnulls, astate->alen * sizeof(bool));
		}
	}


	if (!disnull && !astate->typbyval)
		dvalue = datumCopy(dvalue, astate->typbyval, astate->typlen);

	astate->dvalues[astate->nelems] = dvalue;
	astate->dnulls[astate->nelems] = disnull;
	astate->nelems++;

	MemoryContextSwitchTo(oldcontext);

	return astate;
}
