__lock_set_env_timeout(dbenv, timeout, flags)
	DB_ENV *dbenv;
	db_timeout_t timeout;
	u_int32_t flags;
{
	DB_LOCKREGION *region;
	DB_LOCKTAB *lt;
	DB_THREAD_INFO *ip;
	ENV *env;
	int ret;

	env = dbenv->env;

	ENV_NOT_CONFIGURED(env,
	    env->lk_handle, "DB_ENV->set_env_timeout", DB_INIT_LOCK);

	ret = 0;
	if (LOCKING_ON(env)) {
		lt = env->lk_handle;
		region = lt->reginfo.primary;
		ENV_ENTER(env, ip);
		LOCK_REGION_LOCK(env);
		switch (flags) {
		case DB_SET_LOCK_TIMEOUT:
			region->lk_timeout = timeout;
			break;
		case DB_SET_TXN_TIMEOUT:
			region->tx_timeout = timeout;
			break;
		default:
			ret = 1;
			break;
		}
		LOCK_REGION_UNLOCK(env);
		ENV_LEAVE(env, ip);
	} else
		switch (flags) {
		case DB_SET_LOCK_TIMEOUT:
			dbenv->lk_timeout = timeout;
			break;
		case DB_SET_TXN_TIMEOUT:
			dbenv->tx_timeout = timeout;
			break;
		default:
			ret = 1;
			break;
		}

	if (ret)
		ret = __db_ferr(env, "DB_ENV->set_timeout", 0);

	return (ret);
}
