parserep(register const struct sunrpc_msg *rp, register u_int length)
{
	register const u_int32_t *dp;
	u_int len;
	enum sunrpc_accept_stat astat;


	dp = ((const u_int32_t *)&rp->rm_reply) + 1;
	TCHECK(dp[1]);
	len = EXTRACT_32BITS(&dp[1]);
	if (len >= length)
		return (NULL);


	dp += (len + (2*sizeof(u_int32_t) + 3)) / sizeof(u_int32_t);
	TCHECK2(dp[0], 0);


	astat = (enum sunrpc_accept_stat) EXTRACT_32BITS(dp);
	switch (astat) {

	case SUNRPC_SUCCESS:
		break;

	case SUNRPC_PROG_UNAVAIL:
		printf(" PROG_UNAVAIL");
		nfserr = 1;
		return (NULL);

	case SUNRPC_PROG_MISMATCH:
		printf(" PROG_MISMATCH");
		nfserr = 1;
		return (NULL);

	case SUNRPC_PROC_UNAVAIL:
		printf(" PROC_UNAVAIL");
		nfserr = 1;
		return (NULL);

	case SUNRPC_GARBAGE_ARGS:
		printf(" GARBAGE_ARGS");
		nfserr = 1;
		return (NULL);

	case SUNRPC_SYSTEM_ERR:
		printf(" SYSTEM_ERR");
		nfserr = 1;
		return (NULL);

	default:
		printf(" ar_stat %d", astat);
		nfserr = 1;
		return (NULL);
	}

	TCHECK2(*dp, sizeof(astat));
	return ((u_int32_t *) (sizeof(astat) + ((char *)dp)));
trunc:
	return (0);
}
