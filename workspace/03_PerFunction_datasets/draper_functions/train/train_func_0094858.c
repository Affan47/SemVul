range_in(PG_FUNCTION_ARGS)
{
	char	   *input_str = PG_GETARG_CSTRING(0);
	Oid			rngtypoid = PG_GETARG_OID(1);
	Oid			typmod = PG_GETARG_INT32(2);
	RangeType  *range;
	RangeIOData *cache;
	char		flags;
	char	   *lbound_str;
	char	   *ubound_str;
	RangeBound	lower;
	RangeBound	upper;

	cache = get_range_io_data(fcinfo, rngtypoid, IOFunc_input);


	range_parse(input_str, &flags, &lbound_str, &ubound_str);


	if (RANGE_HAS_LBOUND(flags))
		lower.val = InputFunctionCall(&cache->proc, lbound_str,
									  cache->typioparam, typmod);
	if (RANGE_HAS_UBOUND(flags))
		upper.val = InputFunctionCall(&cache->proc, ubound_str,
									  cache->typioparam, typmod);

	lower.infinite = (flags & RANGE_LB_INF) != 0;
	lower.inclusive = (flags & RANGE_LB_INC) != 0;
	lower.lower = true;
	upper.infinite = (flags & RANGE_UB_INF) != 0;
	upper.inclusive = (flags & RANGE_UB_INC) != 0;
	upper.lower = false;


	range = make_range(cache->typcache, &lower, &upper, flags & RANGE_EMPTY);

	PG_RETURN_RANGE(range);
}
