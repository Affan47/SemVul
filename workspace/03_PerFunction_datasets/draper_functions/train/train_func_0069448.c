__env_get_memory_init(dbenv, type, countp)
	DB_ENV *dbenv;
	DB_MEM_CONFIG type;
	u_int32_t *countp;
{
	ENV *env;

	env = dbenv->env;

	switch (type) {
	case DB_MEM_LOCK:
		ENV_NOT_CONFIGURED(env,
		    env->lk_handle, "DB_ENV->get_memory_init", DB_INIT_LOCK);
		if (LOCKING_ON(env))
			*countp = ((DB_LOCKREGION *)
			    env->lk_handle->reginfo.primary)->stat.st_initlocks;
		else
			*countp = dbenv->lk_init;
		break;
	case DB_MEM_LOCKOBJECT:
		ENV_NOT_CONFIGURED(env,
		    env->lk_handle, "DB_ENV->get_memory_init", DB_INIT_LOCK);
		if (LOCKING_ON(env))
			*countp = ((DB_LOCKREGION *) env->
			    lk_handle->reginfo.primary)->stat.st_initobjects;
		else
			*countp = dbenv->lk_init_objects;
		break;
	case DB_MEM_LOCKER:
		ENV_NOT_CONFIGURED(env,
		    env->lk_handle, "DB_ENV->get_memory_init", DB_INIT_LOCK);
		if (LOCKING_ON(env))
			*countp = ((DB_LOCKREGION *) env->
			    lk_handle->reginfo.primary)->stat.st_initlockers;
		else
			*countp = dbenv->lk_init_lockers;
		break;
	case DB_MEM_LOGID:
		ENV_NOT_CONFIGURED(env,
		    env->lg_handle, "DB_ENV->get_memory_init", DB_INIT_LOG);

		if (LOGGING_ON(env))
			*countp = ((LOG *)env->lg_handle->
			    reginfo.primary)->stat.st_fileid_init;
		else
			*countp = dbenv->lg_fileid_init;
		break;
	case DB_MEM_TRANSACTION:
		ENV_NOT_CONFIGURED(env,
		    env->tx_handle, "DB_ENV->memory_init", DB_INIT_TXN);

		if (TXN_ON(env))
			*countp = ((DB_TXNREGION *)
			    env->tx_handle->reginfo.primary)->inittxns;
		else
			*countp = dbenv->tx_init;
		break;
	case DB_MEM_THREAD:

		*countp = dbenv->thr_init;
		break;
	}

	return (0);
}
