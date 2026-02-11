bpcharne(PG_FUNCTION_ARGS)
{
	BpChar	   *arg1 = PG_GETARG_BPCHAR_PP(0);
	BpChar	   *arg2 = PG_GETARG_BPCHAR_PP(1);
	int			len1,
				len2;
	bool		result;

	len1 = bcTruelen(arg1);
	len2 = bcTruelen(arg2);


	if (len1 != len2)
		result = true;
	else
		result = (strncmp(VARDATA_ANY(arg1), VARDATA_ANY(arg2), len1) != 0);

	PG_FREE_IF_COPY(arg1, 0);
	PG_FREE_IF_COPY(arg2, 1);

	PG_RETURN_BOOL(result);
}
