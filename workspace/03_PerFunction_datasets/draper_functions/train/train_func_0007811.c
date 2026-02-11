linger_timeout(time_t event_time, void *arg)
{
	PRBool delete_now;
	Repl_Connection *conn = (Repl_Connection *)arg;

	LDAPDebug( LDAP_DEBUG_TRACE, "=> linger_timeout\n", 0, 0, 0 );

	PR_ASSERT(NULL != conn);
	slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
		"%s: Linger timeout has expired on the connection\n",
		agmt_get_long_name(conn->agmt));
	PR_Lock(conn->lock);
	if (conn->linger_active)
	{
		conn->linger_active = PR_FALSE;
		conn->linger_event = NULL;
		close_connection_internal(conn);
	}
	delete_now = conn->delete_after_linger;
	PR_Unlock(conn->lock);
	if (delete_now)
	{
		windows_conn_delete_internal(conn);
	}
	LDAPDebug( LDAP_DEBUG_TRACE, "<= linger_timeout\n", 0, 0, 0 );
}
