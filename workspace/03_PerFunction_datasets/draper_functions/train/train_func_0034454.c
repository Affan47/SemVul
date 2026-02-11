__repmgr_site_info_marshal(env, argp, bp, max, lenp)
	ENV *env;
	__repmgr_site_info_args *argp;
	u_int8_t *bp;
	size_t *lenp, max;
{
	u_int8_t *start;

	if (max < __REPMGR_SITE_INFO_SIZE
	    + (size_t)argp->host.size)
		return (ENOMEM);
	start = bp;

	DB_HTONL_COPYOUT(env, bp, argp->host.size);
	if (argp->host.size > 0) {
		memcpy(bp, argp->host.data, argp->host.size);
		bp += argp->host.size;
	}
	DB_HTONS_COPYOUT(env, bp, argp->port);
	DB_HTONL_COPYOUT(env, bp, argp->status);
	DB_HTONL_COPYOUT(env, bp, argp->flags);

	*lenp = (size_t)(bp - start);
	return (0);
}
