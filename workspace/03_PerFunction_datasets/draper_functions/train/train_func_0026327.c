bpchargt(PG_FUNCTION_ARGS)
{
	BpChar	   *arg1 = PG_GETARG_BPCHAR_P(0);
	BpChar	   *arg2 = PG_GETARG_BPCHAR_P(1);
	int			len1,
				len2;
	int			cmp;

	len1 = bcTruelen(arg1);
	len2 = bcTruelen(arg2);

	cmp = varstr_cmp(VARDATA(arg1), len1, VARDATA(arg2), len2);

	PG_FREE_IF_COPY(arg1, 0);
	PG_FREE_IF_COPY(arg2, 1);

	PG_RETURN_BOOL(cmp > 0);
}
