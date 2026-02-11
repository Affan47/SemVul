__repmgr_net_close(env)
	ENV *env;
{
	DB_REP *db_rep;
	REP *rep;
	REPMGR_SITE *site;
	u_int eid;
	int ret;

	db_rep = env->rep_handle;
	rep = db_rep->region;

	if ((ret = __repmgr_each_connection(env, final_cleanup, NULL,
	    FALSE)) == 0) {
		FOR_EACH_REMOTE_SITE_INDEX(eid) {
			site = SITE_FROM_EID(eid);
			site->ref.conn.in = NULL;
			site->ref.conn.out = NULL;
		}
	}

	if (db_rep->listen_fd != INVALID_SOCKET) {
		if (closesocket(db_rep->listen_fd) == SOCKET_ERROR && ret == 0)
			ret = net_errno;
		db_rep->listen_fd = INVALID_SOCKET;
		rep->listener = 0;
	}
	return (ret);
}
