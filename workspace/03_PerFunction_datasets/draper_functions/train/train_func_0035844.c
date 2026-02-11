gin_tsquery_triconsistent(PG_FUNCTION_ARGS)
{
	GinTernaryValue *check = (GinTernaryValue *) PG_GETARG_POINTER(0);


	TSQuery		query = PG_GETARG_TSQUERY(2);


	Pointer    *extra_data = (Pointer *) PG_GETARG_POINTER(4);
	GinTernaryValue res = GIN_FALSE;
	bool		recheck;


	recheck = false;

	if (query->size > 0)
	{
		QueryItem  *item;
		GinChkVal	gcv;


		gcv.first_item = item = GETQUERY(query);
		gcv.check = check;
		gcv.map_item_operand = (int *) (extra_data[0]);
		gcv.need_recheck = &recheck;

		res = TS_execute_ternary(GETQUERY(query),
								 &gcv,
								 checkcondition_gin);

		if (res == GIN_TRUE && recheck)
			res = GIN_MAYBE;
	}

	PG_RETURN_GIN_TERNARY_VALUE(res);
}
