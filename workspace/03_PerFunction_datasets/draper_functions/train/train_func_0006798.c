regexp_split_to_array(PG_FUNCTION_ARGS)
{
	ArrayBuildState *astate = NULL;
	regexp_matches_ctx *splitctx;

	splitctx = setup_regexp_matches(PG_GETARG_TEXT_PP(0),
									PG_GETARG_TEXT_PP(1),
									PG_GETARG_TEXT_PP_IF_EXISTS(2),
									true, false, true);

	while (splitctx->next_match <= splitctx->nmatches)
	{
		astate = accumArrayResult(astate,
								  build_regexp_split_result(splitctx),
								  false,
								  TEXTOID,
								  CurrentMemoryContext);
		splitctx->next_match++;
	}


	PG_RETURN_ARRAYTYPE_P(makeArrayResult(astate, CurrentMemoryContext));
}
