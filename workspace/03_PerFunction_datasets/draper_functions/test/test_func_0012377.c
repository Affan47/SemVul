__mutex_alloc(env, alloc_id, flags, indxp)
	ENV *env;
	int alloc_id;
	u_int32_t flags;
	db_mutex_t *indxp;
{

	*indxp = MUTEX_INVALID;


	if (alloc_id != MTX_APPLICATION && alloc_id != MTX_MUTEX_TEST &&
	    (F_ISSET(env->dbenv, DB_ENV_NOLOCKING) ||
	    (!F_ISSET(env, ENV_THREAD) &&
	    (LF_ISSET(DB_MUTEX_PROCESS_ONLY) || F_ISSET(env, ENV_PRIVATE)))))
		return (0);


	if (F_ISSET(env, ENV_PRIVATE))
		LF_SET(DB_MUTEX_PROCESS_ONLY);


	if (!MUTEX_ON(env)) {
		__db_errx(env, DB_STR("2033",
		    "Mutex allocated before mutex region."));
		return (__env_panic(env, EINVAL));
	}
	return (__mutex_alloc_int(env, 1, alloc_id, flags, indxp));
}
