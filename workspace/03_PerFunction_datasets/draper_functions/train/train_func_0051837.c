makeMdArrayResult(ArrayBuildState *astate,
				  int ndims,
				  int *dims,
				  int *lbs,
				  MemoryContext rcontext,
				  bool release)
{
	ArrayType  *result;
	MemoryContext oldcontext;


	oldcontext = MemoryContextSwitchTo(rcontext);

	result = construct_md_array(astate->dvalues,
								astate->dnulls,
								ndims,
								dims,
								lbs,
								astate->element_type,
								astate->typlen,
								astate->typbyval,
								astate->typalign);

	MemoryContextSwitchTo(oldcontext);


	if (release)
	{
		Assert(astate->private_cxt);
		MemoryContextDelete(astate->mcontext);
	}

	return PointerGetDatum(result);
}
