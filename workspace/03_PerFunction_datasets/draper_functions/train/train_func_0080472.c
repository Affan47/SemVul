__memp_set_mp_max_write(dbenv, maxwrite, maxwrite_sleep)
	DB_ENV *dbenv;
	int maxwrite;
	db_timeout_t maxwrite_sleep;
{
	DB_MPOOL *dbmp;
	DB_THREAD_INFO *ip;
	ENV *env;
	MPOOL *mp;

	env = dbenv->env;

	ENV_NOT_CONFIGURED(env,
	    env->mp_handle, "DB_ENV->set_mp_max_write", DB_INIT_MPOOL);

	if (MPOOL_ON(env)) {
		dbmp = env->mp_handle;
		mp = dbmp->reginfo[0].primary;
		ENV_ENTER(env, ip);
		MPOOL_SYSTEM_LOCK(env);
		mp->mp_maxwrite = maxwrite;
		mp->mp_maxwrite_sleep = maxwrite_sleep;
		MPOOL_SYSTEM_UNLOCK(env);
		ENV_LEAVE(env, ip);
	} else {
		dbenv->mp_maxwrite = maxwrite;
		dbenv->mp_maxwrite_sleep = maxwrite_sleep;
	}
	return (0);
}
