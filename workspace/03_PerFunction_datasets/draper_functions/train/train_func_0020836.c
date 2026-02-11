__logc_close_pp(logc, flags)
	DB_LOGC *logc;
	u_int32_t flags;
{
	DB_THREAD_INFO *ip;
	ENV *env;
	int ret;

	env = logc->env;

	if ((ret = __db_fchk(env, "DB_LOGC->close", flags, 0)) != 0)
		return (ret);

	ENV_ENTER(env, ip);
	REPLICATION_WRAP(env, (__logc_close(logc)), 0, ret);
	ENV_LEAVE(env, ip);
	return (ret);
}
