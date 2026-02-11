conn_read_entry_attribute(Repl_Connection *conn, const char *dn,
	char *type, struct berval ***returned_bvals)
{
	ConnResult return_value;
	int ldap_rc;
	LDAPControl *server_controls[2];
	LDAPMessage *res = NULL;
	char *attrs[2];

	PR_ASSERT(NULL != type);
	if (conn_connected(conn))
	{
		server_controls[0] = &manageDSAITControl;
		server_controls[1] = NULL;
		attrs[0] = type;
		attrs[1] = NULL;
		ldap_rc = ldap_search_ext_s(conn->ld, dn, LDAP_SCOPE_BASE,
			"(objectclass=*)", attrs, 0 ,
			server_controls, NULL ,
			&conn->timeout, 0 , &res);
		if (LDAP_SUCCESS == ldap_rc)
		{
			LDAPMessage *entry = ldap_first_entry(conn->ld, res);
			if (NULL != entry)
			{
				*returned_bvals = ldap_get_values_len(conn->ld, entry, type);
			}
			return_value = CONN_OPERATION_SUCCESS;
		}
		else if (IS_DISCONNECT_ERROR(ldap_rc))
		{
			conn_disconnect(conn);
			return_value = CONN_NOT_CONNECTED;
		}
		else
		{
			return_value = CONN_OPERATION_FAILED;
		}
		conn->last_ldap_error = ldap_rc;
		if (NULL != res)
		{
			ldap_msgfree(res);
			res = NULL;
		}
	}
	else
	{
		return_value = CONN_NOT_CONNECTED;
	}
	return return_value;
}
