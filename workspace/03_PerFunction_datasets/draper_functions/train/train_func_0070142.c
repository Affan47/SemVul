parse_syslog_level( const char *arg, int *levelp )
{
	static slap_verbmasks	str2syslog_level[] = {
		{ BER_BVC( "EMERG" ),	LOG_EMERG },
		{ BER_BVC( "ALERT" ),	LOG_ALERT },
		{ BER_BVC( "CRIT" ),	LOG_CRIT },
		{ BER_BVC( "ERR" ),	LOG_ERR },
		{ BER_BVC( "WARNING" ),	LOG_WARNING },
		{ BER_BVC( "NOTICE" ),	LOG_NOTICE },
		{ BER_BVC( "INFO" ),	LOG_INFO },
		{ BER_BVC( "DEBUG" ),	LOG_DEBUG },
		{ BER_BVNULL, 0 }
	};
	int i = verb_to_mask( arg, str2syslog_level );
	if ( BER_BVISNULL( &str2syslog_level[ i ].word ) ) {
		Debug( LDAP_DEBUG_ANY,
			"unknown syslog level \"%s\".\n",
			arg, 0, 0 );
		return 1;
	}

	*levelp = str2syslog_level[ i ].mask;

	return 0;
}
