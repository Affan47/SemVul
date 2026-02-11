slapi_str2filter( char *str )
{
	struct slapi_filter	*f = NULL;
	char		*end;

	LDAPDebug( LDAP_DEBUG_FILTER, "slapi_str2filter \"%s\"\n", str, 0, 0 );

	if ( str == NULL || *str == '\0' ) {
		return( NULL );
	}

	switch ( *str ) {
	case '(':
		if ( (end = slapi_find_matching_paren( str )) == NULL ) {
			slapi_filter_free( f, 1 );
			return( NULL );
		}
		*end = '\0';

		str++;
		switch ( *str ) {
		case '&':
			LDAPDebug( LDAP_DEBUG_FILTER, "slapi_str2filter: AND\n",
			    0, 0, 0 );

			str++;
			f = str2list( str, LDAP_FILTER_AND );
			break;

		case '|':
			LDAPDebug( LDAP_DEBUG_FILTER, "put_filter: OR\n",
			    0, 0, 0 );

			str++;
			f = str2list( str, LDAP_FILTER_OR );
			break;

		case '!':
			LDAPDebug( LDAP_DEBUG_FILTER, "put_filter: NOT\n",
			    0, 0, 0 );

			str++;
			f = str2list( str, LDAP_FILTER_NOT );
			break;

		default:
			LDAPDebug( LDAP_DEBUG_FILTER, "slapi_str2filter: simple\n",
			    0, 0, 0 );

			f = str2simple( str , 1 );
			break;
		}
		*end = ')';
		break;

	default:
		LDAPDebug( LDAP_DEBUG_FILTER, "slapi_str2filter: default\n", 0, 0,
		    0 );

		f = str2simple( str , 1 );
		break;
	}

	return( f );
}
