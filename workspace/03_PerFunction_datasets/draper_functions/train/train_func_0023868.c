__repmgr_v4site_info_unmarshal(env, argp, bp, max, nextp)
	ENV *env;
	__repmgr_v4site_info_args *argp;
	u_int8_t *bp;
	size_t max;
	u_int8_t **nextp;
{
	size_t needed;

	needed = __REPMGR_V4SITE_INFO_SIZE;
	if (max < needed)
		goto too_few;
	DB_NTOHL_COPYIN(env, argp->host.size, bp);
	if (argp->host.size == 0)
		argp->host.data = NULL;
	else
		argp->host.data = bp;
	needed += (size_t)argp->host.size;
	if (max < needed)
		goto too_few;
	bp += argp->host.size;
	DB_NTOHS_COPYIN(env, argp->port, bp);
	DB_NTOHL_COPYIN(env, argp->flags, bp);

	if (nextp != NULL)
		*nextp = bp;
	return (0);

too_few:
	__db_errx(env, DB_STR("3675",
	    "Not enough input bytes to fill a __repmgr_v4site_info message"));
	return (EINVAL);
}
