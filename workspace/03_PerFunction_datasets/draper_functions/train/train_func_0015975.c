slap_sasl_setpolicy( const char *arg )
{
	int rc = LDAP_SUCCESS;

	if ( strcasecmp( arg, "none" ) == 0 ) {
		authz_policy = SASL_AUTHZ_NONE;
	} else if ( strcasecmp( arg, "from" ) == 0 ) {
		authz_policy = SASL_AUTHZ_FROM;
	} else if ( strcasecmp( arg, "to" ) == 0 ) {
		authz_policy = SASL_AUTHZ_TO;
	} else if ( strcasecmp( arg, "both" ) == 0 || strcasecmp( arg, "any" ) == 0 ) {
		authz_policy = SASL_AUTHZ_FROM | SASL_AUTHZ_TO;
	} else if ( strcasecmp( arg, "all" ) == 0 ) {
		authz_policy = SASL_AUTHZ_FROM | SASL_AUTHZ_TO | SASL_AUTHZ_AND;
	} else {
		rc = LDAP_OTHER;
	}
	return rc;
}
