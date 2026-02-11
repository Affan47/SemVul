slap_sasl_regexp_config( const char *match, const char *replace )
{
	int rc;
	SaslRegexp_t *reg;

	SaslRegexp = (SaslRegexp_t *) ch_realloc( (char *) SaslRegexp,
	  (nSaslRegexp + 1) * sizeof(SaslRegexp_t) );

	reg = &SaslRegexp[nSaslRegexp];

#ifdef SLAP_AUTH_REWRITE
	rc = slap_sasl_regexp_rewrite_config( "sasl-regexp", 0,
			match, replace, AUTHID_CONTEXT );
#else


	rc = regcomp( &reg->sr_workspace, match, REG_EXTENDED|REG_ICASE );
	if ( rc ) {
		Debug( LDAP_DEBUG_ANY,
			"SASL match pattern %s could not be compiled by regexp engine\n",
			match, 0, 0 );

#ifdef ENABLE_REWRITE

		if ( slapMode == ( SLAP_SERVER_MODE|SLAP_TOOL_MODE )) {
			rewrite_info_init( 0 );
		}
#endif
		return( LDAP_OTHER );
	}

	rc = slap_sasl_rx_off( replace, reg->sr_offset );
#endif
	if ( rc == LDAP_SUCCESS ) {
		reg->sr_match = ch_strdup( match );
		reg->sr_replace = ch_strdup( replace );

		nSaslRegexp++;
	}

	return rc;
}
