__repmgr_channel_close(dbchan, flags)
	DB_CHANNEL *dbchan;
	u_int32_t flags;
{
	ENV *env;
	DB_REP *db_rep;
	DB_THREAD_INFO *ip;
	REPMGR_CONNECTION *conn;
	CHANNEL *channel;
	u_int32_t i;
	int ret, t_ret;

	channel = dbchan->channel;
	env = channel->env;
	ret = __db_fchk(env, "DB_CHANNEL->close", flags, 0);
	db_rep = env->rep_handle;


	ENV_ENTER(env, ip);
	LOCK_MUTEX(db_rep->mutex);
	if (dbchan->eid >= 0) {
		conn = channel->c.conn;
		if (conn->state != CONN_DEFUNCT &&
		    (t_ret = __repmgr_disable_connection(env, conn)) != 0 &&
		    ret == 0)
			ret = t_ret;
		if ((t_ret = __repmgr_decr_conn_ref(env, conn)) != 0 &&
		    ret == 0)
			ret = t_ret;
	} else if (channel->c.conns.cnt > 0) {
		for (i = 0; i < channel->c.conns.cnt; i++)
			if ((conn = channel->c.conns.array[i]) != NULL) {
				if (conn->state != CONN_DEFUNCT &&
				    (t_ret = __repmgr_disable_connection(env,
				    conn)) != 0 && ret == 0)
					ret = t_ret;
				if ((t_ret = __repmgr_decr_conn_ref(env,
				    conn)) != 0 && ret == 0)
					ret = t_ret;
			}
		__os_free(env, channel->c.conns.array);
	}
	UNLOCK_MUTEX(db_rep->mutex);

	if (!IS_VALID_EID(dbchan->eid) && channel->c.conns.mutex != NULL &&
	    (t_ret = __repmgr_destroy_mutex(env,
	    channel->c.conns.mutex)) != 0 && ret == 0)
		ret = t_ret;

	if ((t_ret = __repmgr_wake_main_thread(env)) != 0 && ret == 0)
		ret = t_ret;

	__os_free(env, channel);
	__os_free(env, dbchan);

	ENV_LEAVE(env, ip);
	return (ret);
}
