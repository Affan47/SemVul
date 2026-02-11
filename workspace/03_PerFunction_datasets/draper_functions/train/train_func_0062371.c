gist_box_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	BOX		   *query = PG_GETARG_BOX_P(1);
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);


	bool	   *recheck = (bool *) PG_GETARG_POINTER(4);


	*recheck = false;

	if (DatumGetBoxP(entry->key) == NULL || query == NULL)
		PG_RETURN_BOOL(FALSE);


	if (GIST_LEAF(entry))
		PG_RETURN_BOOL(gist_box_leaf_consistent(DatumGetBoxP(entry->key),
												query,
												strategy));
	else
		PG_RETURN_BOOL(rtree_internal_consistent(DatumGetBoxP(entry->key),
												 query,
												 strategy));
}
