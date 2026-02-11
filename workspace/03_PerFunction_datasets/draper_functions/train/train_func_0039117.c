ginarrayconsistent(PG_FUNCTION_ARGS)
{
	bool	   *check = (bool *) PG_GETARG_POINTER(0);
	StrategyNumber strategy = PG_GETARG_UINT16(1);
	ArrayType  *query = PG_GETARG_ARRAYTYPE_P(2);
	int			res,
				i,
				nentries;


	switch (strategy)
	{
		case GinOverlapStrategy:
		case GinContainedStrategy:

			res = TRUE;
			break;
		case GinContainsStrategy:
		case GinEqualStrategy:
			nentries = ArrayGetNItems(ARR_NDIM(query), ARR_DIMS(query));
			res = TRUE;
			for (i = 0; i < nentries; i++)
				if (!check[i])
				{
					res = FALSE;
					break;
				}
			break;
		default:
			elog(ERROR, "ginarrayconsistent: unknown strategy number: %d",
				 strategy);
			res = FALSE;
	}

	PG_RETURN_BOOL(res);
}
