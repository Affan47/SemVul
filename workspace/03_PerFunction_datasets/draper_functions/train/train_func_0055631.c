do_simple_bind (Repl_Connection *conn, LDAP *ld, char * binddn, char *password)
{
	int msgid;

	LDAPDebug( LDAP_DEBUG_TRACE, "=> do_simple_bind\n", 0, 0, 0 );

	if( LDAP_SUCCESS != slapi_ldap_bind( ld, binddn, password, LDAP_SASL_SIMPLE, NULL, NULL, NULL, &msgid ) )
	{
		char *ldaperrtext = NULL;
		int ldaperr;
		int prerr = PR_GetError();

		ldaperr = slapi_ldap_get_lderrno( ld, NULL, &ldaperrtext );

		if (conn->last_ldap_error != ldaperr)
		{
			conn->last_ldap_error = ldaperr;
			slapi_log_error(SLAPI_LOG_FATAL, windows_repl_plugin_name,
				"%s: Simple bind failed, "
				SLAPI_COMPONENT_NAME_LDAPSDK " error %d (%s) (%s), "
				SLAPI_COMPONENT_NAME_NSPR " error %d (%s)\n",
				agmt_get_long_name(conn->agmt),
				ldaperr, ldap_err2string(ldaperr),
				ldaperrtext ? ldaperrtext : "",
				prerr, slapd_pr_strerror(prerr));
		}
	}
	else if (conn->last_ldap_error != LDAP_SUCCESS)
	{
		conn->last_ldap_error = LDAP_SUCCESS;
		slapi_log_error(SLAPI_LOG_FATAL, windows_repl_plugin_name,
			"%s: Simple bind resumed\n",
			agmt_get_long_name(conn->agmt));
	}
	LDAPDebug( LDAP_DEBUG_TRACE, "<= do_simple_bind\n", 0, 0, 0 );
	return msgid;
}
