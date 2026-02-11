send_dirsync_search(Repl_Connection *conn)
{
	ConnResult return_value;

	LDAPDebug( LDAP_DEBUG_TRACE, "=> send_dirsync_search\n", 0, 0, 0 );

	if (windows_conn_connected(conn))
	{
		const char *op_string = NULL;
		int rc;
		int scope = LDAP_SCOPE_SUBTREE;
		const char *userfilter = NULL;
		char *filter = NULL;
		char **attrs = NULL;
		LDAPControl **server_controls = NULL;
		int msgid;
		const char *old_dn = slapi_sdn_get_ndn( windows_private_get_windows_subtree(conn->agmt) );

		char *dn = slapi_ch_strdup(strstr(old_dn, "dc="));
		char **exattrs = NULL;

		if (conn->supports_dirsync == 0)
		{

		} else
		{
			slapi_add_control_ext(&server_controls,
			                      windows_private_dirsync_control(conn->agmt),
			                      0 );
		}

		conn->last_operation = CONN_SEARCH;
		conn->status = STATUS_SEARCHING;
		op_string = "search";

		LDAPDebug( LDAP_DEBUG_REPL, "Calling dirsync search request plugin\n", 0, 0, 0 );
		userfilter = windows_private_get_windows_userfilter(conn->agmt);
		if (userfilter) {
			filter = slapi_ch_strdup(userfilter);
		} else {
			filter = slapi_ch_strdup("(objectclass=*)");
		}

		winsync_plugin_call_dirsync_search_params_cb(conn->agmt, old_dn, &dn, &scope, &filter,
		                                             &attrs, &server_controls);
		exattrs = windows_private_get_range_attrs(conn->agmt);
		charray_merge(&attrs, exattrs, 0 );
		slapi_ch_free((void **)&exattrs);

		LDAPDebug( LDAP_DEBUG_REPL, "Sending dirsync search request\n", 0, 0, 0 );

		rc = ldap_search_ext( conn->ld, dn, scope, filter, attrs, PR_FALSE, server_controls,
                              NULL , 0,0, &msgid);

		if (LDAP_SUCCESS == rc)
		{
			return_value = 0;
		}
		else
		{
            slapi_log_error(SLAPI_LOG_FATAL, windows_repl_plugin_name,
					"%s: Failed to get %s operation: LDAP error %d (%s)\n",
					agmt_get_long_name(conn->agmt),
					op_string, rc, ldap_err2string(rc));
			conn->last_ldap_error = rc;
			if (IS_DISCONNECT_ERROR(rc))
			{
				windows_conn_disconnect(conn);
				return_value = CONN_NOT_CONNECTED;
			}
			else
			{
				conn->status = STATUS_CONNECTED;
				return_value = CONN_OPERATION_FAILED;
			}
		}

		slapi_ch_free_string(&dn);
		slapi_ch_free_string(&filter);
		slapi_ch_array_free(attrs);
		attrs = NULL;
		ldap_controls_free(server_controls);
		server_controls = NULL;
	}
	else
	{


		return_value = CONN_NOT_CONNECTED;
	}
	LDAPDebug( LDAP_DEBUG_TRACE, "<= send_dirsync_search\n", 0, 0, 0 );
	return return_value;
}
