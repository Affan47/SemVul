__repmgr_hold_master_role(env, conn)
	ENV *env;
	REPMGR_CONNECTION *conn;
{
	DB_REP *db_rep;
	REP *rep;
	int ret, t_ret;

	db_rep = env->rep_handle;
	rep = db_rep->region;

	LOCK_MUTEX(db_rep->mutex);
	if ((ret = __repmgr_await_gmdbop(env)) == 0) {


		if (rep->master_id != db_rep->self_eid ||
		    db_rep->client_intent)
			ret = DB_REP_UNAVAIL;
		else
			db_rep->gmdb_busy = TRUE;
	}
	UNLOCK_MUTEX(db_rep->mutex);
	if (conn != NULL && ret == DB_REP_UNAVAIL &&
	    (t_ret = reject_fwd(env, conn)) != 0)
		ret = t_ret;
	return (ret);
}
