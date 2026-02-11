__rep_elect_pp(dbenv, given_nsites, nvotes, flags)
	DB_ENV *dbenv;
	u_int32_t given_nsites, nvotes;
	u_int32_t flags;
{
	ENV *env;
	DB_REP *db_rep;
	DB_THREAD_INFO *ip;
	int ret;

	env = dbenv->env;
	db_rep = env->rep_handle;
	ret = 0;

	ENV_REQUIRES_CONFIG_XX(
	    env, rep_handle, "DB_ENV->rep_elect", DB_INIT_REP);

	if (APP_IS_REPMGR(env)) {
		__db_errx(env, DB_STR("3527",
"DB_ENV->rep_elect: cannot call from Replication Manager application"));
		return (EINVAL);
	}


	if (db_rep->send == NULL) {
		__db_errx(env, DB_STR("3528",
    "DB_ENV->rep_elect: must be called after DB_ENV->rep_set_transport"));
		return (EINVAL);
	}

	if (!IS_REP_STARTED(env)) {
		__db_errx(env, DB_STR("3529",
	    "DB_ENV->rep_elect: must be called after DB_ENV->rep_start"));
		return (EINVAL);
	}

	if (IS_USING_LEASES(env) && given_nsites != 0) {
		__db_errx(env, DB_STR("3530",
	    "DB_ENV->rep_elect: nsites must be zero if leases configured"));
		return (EINVAL);
	}

	ENV_ENTER(env, ip);
	ret = __rep_elect_int(env, given_nsites, nvotes, flags);
	ENV_LEAVE(env, ip);


	if (ret == DB_REP_IGNORE)
		ret = 0;
	return (ret);
}
