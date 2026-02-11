__rep_logready(env, rep, savetime, last_lsnp)
	ENV *env;
	REP *rep;
	time_t savetime;
	DB_LSN *last_lsnp;
{
	REGENV *renv;
	REGINFO *infop;
	int ret;

	infop = env->reginfo;
	renv = infop->primary;
	if ((ret = __log_flush(env, NULL)) != 0)
		goto err;
	if ((ret = __rep_verify_match(env, last_lsnp, savetime)) != 0)
		goto err;

	REP_SYSTEM_LOCK(env);
	ZERO_LSN(rep->first_lsn);

	if (rep->originfo_off != INVALID_ROFF) {
		MUTEX_LOCK(env, renv->mtx_regenv);
		__env_alloc_free(infop, R_ADDR(infop, rep->originfo_off));
		MUTEX_UNLOCK(env, renv->mtx_regenv);
		rep->originfo_off = INVALID_ROFF;
	}

	rep->sync_state = SYNC_OFF;
	F_SET(rep, REP_F_NIMDBS_LOADED);
	ret = __rep_notify_threads(env, AWAIT_NIMDB);
	REP_SYSTEM_UNLOCK(env);
	if (ret != 0)
		goto err;

	return (0);

err:
	DB_ASSERT(env, ret != DB_REP_WOULDROLLBACK);
	__db_errx(env, DB_STR("3502",
	    "Client initialization failed.  Need to manually restore client"));
	return (__env_panic(env, ret));
}
