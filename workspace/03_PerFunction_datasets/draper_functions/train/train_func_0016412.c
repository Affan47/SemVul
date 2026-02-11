accumArrayResultAny(ArrayBuildStateAny *astate,
					Datum dvalue, bool disnull,
					Oid input_type,
					MemoryContext rcontext)
{
	if (astate == NULL)
		astate = initArrayResultAny(input_type, rcontext, true);

	if (astate->scalarstate)
		(void) accumArrayResult(astate->scalarstate,
								dvalue, disnull,
								input_type, rcontext);
	else
		(void) accumArrayResultArr(astate->arraystate,
								   dvalue, disnull,
								   input_type, rcontext);

	return astate;
}
