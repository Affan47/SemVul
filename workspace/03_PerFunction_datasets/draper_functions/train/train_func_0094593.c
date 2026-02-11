windows_delete_local_entry(Slapi_DN *sdn){

	Slapi_PBlock *pb = NULL;
	int return_value = 0;

	LDAPDebug( LDAP_DEBUG_TRACE, "=> windows_delete_local_entry\n", 0, 0, 0 );

	pb = slapi_pblock_new();
	slapi_delete_internal_set_pb(pb, slapi_sdn_get_dn(sdn), NULL, NULL, repl_get_plugin_identity(PLUGIN_MULTIMASTER_REPLICATION), 0);
	slapi_delete_internal_pb(pb);
	slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &return_value);
	slapi_pblock_destroy(pb);

	if (return_value) {
		slapi_log_error(SLAPI_LOG_REPL, windows_repl_plugin_name,
			"delete operation on local entry %s returned: %d\n", slapi_sdn_get_dn(sdn), return_value);
	}
	LDAPDebug( LDAP_DEBUG_TRACE, "<= windows_delete_local_entry: %d\n", return_value, 0, 0 );

	return return_value;
}
