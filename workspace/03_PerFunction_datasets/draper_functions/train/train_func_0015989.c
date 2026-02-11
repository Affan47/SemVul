acct_policy_load_config_startup( Slapi_PBlock* pb, void* plugin_id ) {
	acctPluginCfg *newcfg;
	Slapi_Entry *config_entry = NULL;
	Slapi_DN *config_sdn = NULL;
	int rc;


	config_sdn = slapi_sdn_new_normdn_byref( PLUGIN_CONFIG_DN );
	rc = slapi_search_internal_get_entry( config_sdn, NULL, &config_entry,
		plugin_id);
	slapi_sdn_free( &config_sdn );

	if( rc != LDAP_SUCCESS || config_entry == NULL ) {
		slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
			"Failed to retrieve configuration entry %s: %d\n",
			PLUGIN_CONFIG_DN, rc );
		return( -1 );
	}

	newcfg = get_config();
	rc = acct_policy_entry2config( config_entry, newcfg );

	slapi_entry_free( config_entry );

	return( rc );
}
