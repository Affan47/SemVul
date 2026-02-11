__rep_set_timeout(dbenv, which, timeout)
	DB_ENV *dbenv;
	int which;
	db_timeout_t timeout;
{
	DB_REP *db_rep;
	DB_THREAD_INFO *ip;
	ENV *env;
	REP *rep;
	int repmgr_timeout, ret;

	env = dbenv->env;
	db_rep = env->rep_handle;
	rep = db_rep->region;
	ret = 0;
	repmgr_timeout = 0;

	if (timeout == 0 && (which == DB_REP_CONNECTION_RETRY ||
	    which == DB_REP_ELECTION_TIMEOUT || which == DB_REP_LEASE_TIMEOUT ||
	    which == DB_REP_ELECTION_RETRY)) {
		__db_errx(env, DB_STR("3566", "timeout value must be > 0"));
		return (EINVAL);
	}

	if (which == DB_REP_ACK_TIMEOUT || which == DB_REP_CONNECTION_RETRY ||
	    which == DB_REP_ELECTION_RETRY ||
	    which == DB_REP_HEARTBEAT_MONITOR ||
	    which == DB_REP_HEARTBEAT_SEND)
		repmgr_timeout = 1;

	ENV_NOT_CONFIGURED(
	    env, db_rep->region, "DB_ENV->rep_set_timeout", DB_INIT_REP);

	if (APP_IS_BASEAPI(env) && repmgr_timeout) {
		__db_errx(env, DB_STR_A("3567",
"%scannot set Replication Manager timeout from base replication application",
		    "%s"), "DB_ENV->rep_set_timeout:");
		return (EINVAL);
	}
	if (which == DB_REP_LEASE_TIMEOUT && IS_REP_STARTED(env)) {
		ret = EINVAL;
		__db_errx(env, DB_STR_A("3568",
"%s: lease timeout must be set before DB_ENV->rep_start.",
		    "%s"), "DB_ENV->rep_set_timeout");
		return (EINVAL);
	}

	switch (which) {
	case DB_REP_CHECKPOINT_DELAY:
		if (REP_ON(env))
			rep->chkpt_delay = timeout;
		else
			db_rep->chkpt_delay = timeout;
		break;
	case DB_REP_ELECTION_TIMEOUT:
		if (REP_ON(env))
			rep->elect_timeout = timeout;
		else
			db_rep->elect_timeout = timeout;
		break;
	case DB_REP_FULL_ELECTION_TIMEOUT:
		if (REP_ON(env))
			rep->full_elect_timeout = timeout;
		else
			db_rep->full_elect_timeout = timeout;
		break;
	case DB_REP_LEASE_TIMEOUT:
		if (REP_ON(env))
			rep->lease_timeout = timeout;
		else
			db_rep->lease_timeout = timeout;
		break;
#ifdef HAVE_REPLICATION_THREADS
	case DB_REP_ACK_TIMEOUT:
		if (REP_ON(env))
			rep->ack_timeout = timeout;
		else
			db_rep->ack_timeout = timeout;
		ADJUST_AUTOTAKEOVER_WAITS(db_rep, timeout);
		break;
	case DB_REP_CONNECTION_RETRY:
		if (REP_ON(env))
			rep->connection_retry_wait = timeout;
		else
			db_rep->connection_retry_wait = timeout;
		break;
	case DB_REP_ELECTION_RETRY:
		if (REP_ON(env))
			rep->election_retry_wait = timeout;
		else
			db_rep->election_retry_wait = timeout;
		break;
	case DB_REP_HEARTBEAT_MONITOR:
		if (REP_ON(env))
			rep->heartbeat_monitor_timeout = timeout;
		else
			db_rep->heartbeat_monitor_timeout = timeout;
		break;
	case DB_REP_HEARTBEAT_SEND:
		if (REP_ON(env))
			rep->heartbeat_frequency = timeout;
		else
			db_rep->heartbeat_frequency = timeout;
		break;
#endif
	default:
		__db_errx(env, DB_STR("3569",
	    "Unknown timeout type argument to DB_ENV->rep_set_timeout"));
		ret = EINVAL;
	}


	if (ret == 0 && repmgr_timeout)
		APP_SET_REPMGR(env);
	return (ret);
}
