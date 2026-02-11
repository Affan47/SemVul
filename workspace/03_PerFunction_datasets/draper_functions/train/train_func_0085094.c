parsecreateopres(const u_int32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(dp, &er)))
		return (0);
	if (er)
		dp = parse_wcc_data(dp, verbose);
	else {
		TCHECK(dp[0]);
		if (!EXTRACT_32BITS(&dp[0]))
			return (dp + 1);
		dp++;
		if (!(dp = parsefh(dp, 1)))
			return (0);
		if (verbose) {
			if (!(dp = parse_post_op_attr(dp, verbose)))
				return (0);
			if (vflag > 1) {
				printf(" dir attr:");
				dp = parse_wcc_data(dp, verbose);
			}
		}
	}
	return (dp);
trunc:
	return (NULL);
}
