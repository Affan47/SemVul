__db_pthread_mutex_readlock(env, mutex)
	ENV *env;
	db_mutex_t mutex;
{
	DB_ENV *dbenv;
	DB_MUTEX *mutexp;
	int ret;

	dbenv = env->dbenv;

	if (!MUTEX_ON(env) || F_ISSET(dbenv, DB_ENV_NOLOCKING))
		return (0);

	mutexp = MUTEXP_SET(env, mutex);
	DB_ASSERT(env, F_ISSET(mutexp, DB_MUTEX_SHARED));

	CHECK_MTX_THREAD(env, mutexp);

#if defined(HAVE_STATISTICS)


	if (F_ISSET(mutexp, DB_MUTEX_LOCKED))
		STAT_INC(env,
		    mutex, set_rd_wait, mutexp->mutex_set_rd_wait, mutex);
	else
		STAT_INC(env,
		    mutex, set_rd_nowait, mutexp->mutex_set_rd_nowait, mutex);
#endif

	PERFMON4(env, mutex, suspend, mutex, FALSE, mutexp->alloc_id, mutexp);
	RET_SET((pthread_rwlock_rdlock(&mutexp->u.rwlock)), ret);
	PERFMON4(env, mutex, resume, mutex, FALSE, mutexp->alloc_id, mutexp);
	DB_ASSERT(env, !F_ISSET(mutexp, DB_MUTEX_LOCKED));
	if (ret != 0)
		goto err;

#ifdef DIAGNOSTIC


	if (F_ISSET(dbenv, DB_ENV_YIELDCPU))
		__os_yield(env, 0, 0);
#endif
	return (0);

err:	__db_err(env, ret, DB_STR("2024", "pthread readlock failed"));
	return (__env_panic(env, ret));
}
