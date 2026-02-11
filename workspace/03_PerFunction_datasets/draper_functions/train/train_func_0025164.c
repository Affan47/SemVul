__rep_get_clockskew(dbenv, fast_clockp, slow_clockp)
	DB_ENV *dbenv;
	u_int32_t *fast_clockp, *slow_clockp;
{
	DB_REP *db_rep;
	DB_THREAD_INFO *ip;
	ENV *env;
	REP *rep;

	env = dbenv->env;
	db_rep = env->rep_handle;

	ENV_NOT_CONFIGURED(
	    env, db_rep->region, "DB_ENV->rep_get_clockskew", DB_INIT_REP);

	if (REP_ON(env)) {
		rep = db_rep->region;
		ENV_ENTER(env, ip);
		REP_SYSTEM_LOCK(env);
		*fast_clockp = rep->clock_skew;
		*slow_clockp = rep->clock_base;
		REP_SYSTEM_UNLOCK(env);
		ENV_LEAVE(env, ip);
	} else {
		*fast_clockp = db_rep->clock_skew;
		*slow_clockp = db_rep->clock_base;
	}

	return (0);
}
