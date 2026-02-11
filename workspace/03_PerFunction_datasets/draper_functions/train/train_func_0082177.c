windows_conn_start_linger(Repl_Connection *conn)
{
	time_t now;

	LDAPDebug( LDAP_DEBUG_TRACE, "=> windows_conn_start_linger\n", 0, 0, 0 );

	PR_ASSERT(NULL != conn);
	slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
		"%s: Beginning linger on the connection\n",
		agmt_get_long_name(conn->agmt));
	if (!windows_conn_connected(conn))
	{
		slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
			"%s: No linger on the closed conn\n",
			agmt_get_long_name(conn->agmt));
		return;
	}
	time(&now);
	PR_Lock(conn->lock);
	if (conn->linger_active)
	{
		slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
			"%s: Linger already active on the connection\n",
			agmt_get_long_name(conn->agmt));
	}
	else
	{
		conn->linger_active = PR_TRUE;
		conn->linger_event = slapi_eq_once(linger_timeout, conn, now + conn->linger_time);
		conn->status = STATUS_LINGERING;
	}
	PR_Unlock(conn->lock);
	LDAPDebug( LDAP_DEBUG_TRACE, "<= windows_conn_start_linger\n", 0, 0, 0 );
}
