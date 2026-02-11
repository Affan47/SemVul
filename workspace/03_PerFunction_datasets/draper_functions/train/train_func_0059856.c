gtsquery_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	TSQuery		query = PG_GETARG_TSQUERY(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);


	bool	   *recheck = (bool *) PG_GETARG_POINTER(4);
	TSQuerySign key = DatumGetTSQuerySign(entry->key);
	TSQuerySign sq = makeTSQuerySign(query);
	bool		retval;


	*recheck = true;

	switch (strategy)
	{
		case RTContainsStrategyNumber:
			if (GIST_LEAF(entry))
				retval = (key & sq) == sq;
			else
				retval = (key & sq) != 0;
			break;
		case RTContainedByStrategyNumber:
			if (GIST_LEAF(entry))
				retval = (key & sq) == key;
			else
				retval = (key & sq) != 0;
			break;
		default:
			retval = FALSE;
	}
	PG_RETURN_BOOL(retval);
}
