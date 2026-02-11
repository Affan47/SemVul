bool_accum(PG_FUNCTION_ARGS)
{
	BoolAggState *state;

	state = PG_ARGISNULL(0) ? NULL : (BoolAggState *) PG_GETARG_POINTER(0);


	if (state == NULL)
		state = makeBoolAggState(fcinfo);

	if (!PG_ARGISNULL(1))
	{
		state->aggcount++;
		if (PG_GETARG_BOOL(1))
			state->aggtrue++;
	}

	PG_RETURN_POINTER(state);
}
