windows_update_remote_entry(Private_Repl_Protocol *prp,Slapi_Entry *remote_entry,Slapi_Entry *local_entry, int is_user)
{
	Slapi_Mods smods = {0};
	int retval = 0;
	int do_modify = 0;
	int ldap_op = 0;
	int ldap_result_code = 0;

	slapi_mods_init (&smods, 0);
	retval = windows_generate_update_mods(prp, remote_entry, local_entry, 1, &smods, &do_modify);

	if (0 == retval && do_modify)
	{
		const char *dn = slapi_sdn_get_dn(slapi_entry_get_sdn_const(remote_entry));
		slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
			"windows_update_remote_entry: modifying entry %s\n", dn);

		retval = windows_conn_send_modify(prp->conn, slapi_sdn_get_dn(slapi_entry_get_sdn_const(remote_entry)),slapi_mods_get_ldapmods_byref(&smods), NULL,NULL);

		windows_conn_get_error(prp->conn, &ldap_op, &ldap_result_code);
		if ((retval != CONN_OPERATION_SUCCESS) && !ldap_result_code) {

			ldap_result_code = LDAP_OPERATIONS_ERROR;
		}
		if (is_user) {
			winsync_plugin_call_post_ad_mod_user_cb(prp->agmt,
						       windows_private_get_raw_entry(prp->agmt),
						       remote_entry,
						       local_entry,
						       &smods, &ldap_result_code);
		} else {
			winsync_plugin_call_post_ad_mod_group_cb(prp->agmt,
							windows_private_get_raw_entry(prp->agmt),
							remote_entry,
							local_entry,
							&smods, &ldap_result_code);
		}

		if ((retval != CONN_OPERATION_SUCCESS) && !ldap_result_code) {
			retval = CONN_OPERATION_SUCCESS;
			windows_conn_set_error(prp->conn, ldap_result_code);
		} else if ((retval == CONN_OPERATION_SUCCESS) && ldap_result_code) {
			retval = CONN_OPERATION_FAILED;
			windows_conn_set_error(prp->conn, ldap_result_code);
		}
	} else
	{
		const char *dn = slapi_sdn_get_dn(slapi_entry_get_sdn_const(remote_entry));
		slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
			"no mods generated for remote entry: %s\n", dn);
	}

	slapi_mods_done(&smods);
	return retval;
}
