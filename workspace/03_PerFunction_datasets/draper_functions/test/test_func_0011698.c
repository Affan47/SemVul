__env_set_blob_threshold(dbenv, bytes, flags)
	DB_ENV *dbenv;
	u_int32_t bytes;
	u_int32_t flags;
{
	ENV *env;
	REGENV *renv;
	REGINFO *infop;
	DB_THREAD_INFO *ip;

	env = dbenv->env;

	if (__db_fchk(dbenv->env, "DB_ENV->set_blob_threshold", flags, 0) != 0)
		return (EINVAL);

	if (REP_ON(dbenv->env) && bytes != 0) {
		__db_errx(dbenv->env,
		    "Blobs are not supported with replication.");
		return (EINVAL);
	}

	if (F_ISSET(env, ENV_OPEN_CALLED)) {
		infop = env->reginfo;
		renv = infop->primary;
		ENV_ENTER(env, ip);
		MUTEX_LOCK(env, renv->mtx_regenv);
		renv->blob_threshold = bytes;
		MUTEX_UNLOCK(env, renv->mtx_regenv);
		ENV_LEAVE(env, ip);
	} else
		dbenv->blob_threshold = bytes;

	return (0);
}
