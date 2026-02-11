phantom_store_setting ( struct settings *settings,
				   struct setting *setting,
				   const void *data, size_t len ) {
	struct phantom_nic *phantom =
		container_of ( settings, struct phantom_nic, settings );
	unsigned int clp_setting;
	int rc;


	clp_setting = phantom_clp_setting ( phantom, setting );
	assert ( clp_setting != 0 );


	if ( ( rc = phantom_clp_store ( phantom, phantom->port,
					clp_setting, data, len ) ) != 0 ) {
		DBGC ( phantom, "Phantom %p could not store setting \"%s\": "
		       "%s\n", phantom, setting->name, strerror ( rc ) );
		return rc;
	}

	return 0;
}
