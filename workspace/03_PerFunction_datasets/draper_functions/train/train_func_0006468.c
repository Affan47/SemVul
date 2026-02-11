parsewccres(const u_int32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	return parse_wcc_data(dp, verbose) != 0;
}
