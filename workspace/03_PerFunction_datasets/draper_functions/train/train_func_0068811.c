acct_policy_init( Slapi_PBlock *pb )
{
	void *plugin_id;
	int enabled;

	slapi_pblock_get(pb, SLAPI_PLUGIN_ENABLED, &enabled);

	if (!enabled) {

		return( CALLBACK_OK );
	}

	if ( slapi_pblock_set( pb, SLAPI_PLUGIN_VERSION,
				SLAPI_PLUGIN_VERSION_01 ) != 0 ||
		slapi_pblock_set( pb, SLAPI_PLUGIN_DESCRIPTION,
				(void *)&plugin_desc ) != 0 ||
		slapi_pblock_set( pb, SLAPI_PLUGIN_START_FN,
				(void *)acct_policy_start ) != 0 ) {
			slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
					"acct_policy_init registration failed\n" );
			return( CALLBACK_ERR );
	}

	if( slapi_pblock_get( pb, SLAPI_PLUGIN_IDENTITY, &plugin_id ) != 0 ) {
		slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
				"acct_policy_init failed to get plugin identity\n" );
		return( CALLBACK_ERR );
	}

	set_identity( plugin_id );


	if( slapi_register_plugin("preoperation", 1, "acct_preop_init",
		acct_preop_init, PRE_PLUGIN_DESC, NULL, plugin_id) != 0 ||
		slapi_register_plugin("postoperation", 1, "acct_postop_init",
		acct_postop_init, POST_PLUGIN_DESC, NULL, plugin_id) != 0 ) {
		slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
			"acct_policy_init failed to register callbacks\n" );
		return( CALLBACK_ERR );
	}

	return( CALLBACK_OK );
}
