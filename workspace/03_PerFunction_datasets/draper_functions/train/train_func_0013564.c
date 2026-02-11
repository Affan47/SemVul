accumArrayResult(ArrayBuildState *astate,
				 Datum dvalue, bool disnull,
				 Oid element_type,
				 MemoryContext rcontext)
{
	MemoryContext oldcontext;

	if (astate == NULL)
	{

		astate = initArrayResult(element_type, rcontext, true);
	}
	else
	{
		Assert(astate->element_type == element_type);
	}

	oldcontext = MemoryContextSwitchTo(astate->mcontext);


	if (astate->nelems >= astate->alen)
	{
		astate->alen *= 2;
		astate->dvalues = (Datum *)
			repalloc(astate->dvalues, astate->alen * sizeof(Datum));
		astate->dnulls = (bool *)
			repalloc(astate->dnulls, astate->alen * sizeof(bool));
	}


	if (!disnull && !astate->typbyval)
	{
		if (astate->typlen == -1)
			dvalue = PointerGetDatum(PG_DETOAST_DATUM_COPY(dvalue));
		else
			dvalue = datumCopy(dvalue, astate->typbyval, astate->typlen);
	}

	astate->dvalues[astate->nelems] = dvalue;
	astate->dnulls[astate->nelems] = disnull;
	astate->nelems++;

	MemoryContextSwitchTo(oldcontext);

	return astate;
}
