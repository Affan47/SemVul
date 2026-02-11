ts_match_tq(PG_FUNCTION_ARGS)
{
	TSVector	vector;
	TSQuery		query = PG_GETARG_TSQUERY(1);
	bool		res;

	vector = DatumGetTSVector(DirectFunctionCall1(to_tsvector,
												  PG_GETARG_DATUM(0)));

	res = DatumGetBool(DirectFunctionCall2(ts_match_vq,
										   TSVectorGetDatum(vector),
										   TSQueryGetDatum(query)));

	pfree(vector);
	PG_FREE_IF_COPY(query, 1);

	PG_RETURN_BOOL(res);
}
