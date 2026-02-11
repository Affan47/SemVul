addr_chk(env, host, port)
	const ENV *env;
	const char *host;
	u_int port;
{
	if (host == NULL || host[0] == '\0') {
		__db_errx(env, DB_STR("3648",
		    "repmgr_site: a host name is required"));
		return (EINVAL);
	}
	if (port == 0 || port > UINT16_MAX) {
		__db_errx(env, DB_STR_A("3649",
		    "repmgr_site: port out of range [1,%u]", "%u"), UINT16_MAX);
		return (EINVAL);
	}
	return (0);
}
