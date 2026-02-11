__repmgr_next_timeout(env, deadline, action)
	ENV *env;
	db_timespec *deadline;
	HEARTBEAT_ACTION *action;
{
	DB_REP *db_rep;
	REP *rep;
	HEARTBEAT_ACTION my_action;
	REPMGR_CONNECTION *conn;
	REPMGR_SITE *master;
	db_timespec t;
	u_int32_t version;

	db_rep = env->rep_handle;
	rep = db_rep->region;

	if (rep->master_id == db_rep->self_eid &&
	    rep->heartbeat_frequency > 0) {
		t = db_rep->last_bcast;
		TIMESPEC_ADD_DB_TIMEOUT(&t, rep->heartbeat_frequency);
		my_action = __repmgr_send_heartbeat;
	} else if ((master = __repmgr_connected_master(env)) != NULL &&
	    !IS_SUBORDINATE(db_rep) &&
	    rep->heartbeat_monitor_timeout > 0) {
		version = 0;
		if ((conn = master->ref.conn.in) != NULL &&
		    IS_READY_STATE(conn->state))
			version = conn->version;
		if ((conn = master->ref.conn.out) != NULL &&
		    IS_READY_STATE(conn->state) &&
		    conn->version > version)
			version = conn->version;
		if (version >= HEARTBEAT_MIN_VERSION) {


			t = master->last_rcvd_timestamp;
			TIMESPEC_ADD_DB_TIMEOUT(&t,
			    rep->heartbeat_monitor_timeout);
			my_action = __repmgr_call_election;
		} else
			return (FALSE);
	} else
		return (FALSE);

	*deadline = t;
	if (action != NULL)
		*action = my_action;
	return (TRUE);
}
