acct_policy_entry2config( Slapi_Entry *e, acctPluginCfg *newcfg ) {
	char *config_val;
	int rc = 0;

	if( newcfg == NULL ) {
		slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
			"Failed to allocate configuration structure\n" );
		return( -1 );
	}

	memset( newcfg, 0, sizeof( acctPluginCfg ) );

	newcfg->state_attr_name = get_attr_string_val( e, CFG_LASTLOGIN_STATE_ATTR );
	if( newcfg->state_attr_name == NULL ) {
		newcfg->state_attr_name = slapi_ch_strdup( DEFAULT_LASTLOGIN_STATE_ATTR );
	} else if (!update_is_allowed_attr(newcfg->state_attr_name)) {

		slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
							 "The configured state attribute [%s] cannot be updated, accounts will always become inactive.\n",
							 newcfg->state_attr_name );
	}

	newcfg->alt_state_attr_name = get_attr_string_val( e, CFG_ALT_LASTLOGIN_STATE_ATTR );


	if( newcfg->alt_state_attr_name == NULL ) {
		newcfg->alt_state_attr_name = slapi_ch_strdup( DEFAULT_ALT_LASTLOGIN_STATE_ATTR );
	} else if ( !strcmp( newcfg->alt_state_attr_name, "1.1" ) ) {
                 slapi_ch_free_string( &newcfg->alt_state_attr_name );
	}

	newcfg->spec_attr_name = get_attr_string_val( e, CFG_SPEC_ATTR );
	if( newcfg->spec_attr_name == NULL ) {
		newcfg->spec_attr_name = slapi_ch_strdup( DEFAULT_SPEC_ATTR );
	}

	newcfg->limit_attr_name = get_attr_string_val( e, CFG_INACT_LIMIT_ATTR );
	if( newcfg->limit_attr_name == NULL ) {
		newcfg->limit_attr_name = slapi_ch_strdup( DEFAULT_INACT_LIMIT_ATTR );
	}

	config_val = get_attr_string_val( e, CFG_RECORD_LOGIN );
	if( config_val &&
		( strcasecmp( config_val, "true" ) == 0 ||
		  strcasecmp( config_val, "yes" ) == 0 ||
		  strcasecmp( config_val, "on" ) == 0 ||
		  strcasecmp( config_val, "1" ) == 0 ) ) {
		newcfg->always_record_login = 1;
	} else {
		newcfg->always_record_login = 0;
	}
	slapi_ch_free_string(&config_val);


	config_val = get_attr_string_val( e, newcfg->limit_attr_name );
	if( config_val ) {
		char *endptr = NULL;
		newcfg->inactivitylimit = strtoul(config_val, &endptr, 10);
		if (endptr && (*endptr != '\0')) {
			slapi_log_error( SLAPI_LOG_FATAL, PLUGIN_NAME,
							 "Failed to parse [%s] from the config entry: [%s] is not a valid unsigned long value\n",
							 newcfg->limit_attr_name, config_val );

			rc = -1;
			newcfg->inactivitylimit = ULONG_MAX;
		}
	} else {
		newcfg->inactivitylimit = ULONG_MAX;
	}
	slapi_ch_free_string(&config_val);

	return( rc );
}
