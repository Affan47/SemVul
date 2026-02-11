slapi_filter_apply( Slapi_Filter *f, FILTER_APPLY_FN fn, void *arg, int *error_code )
{
	switch ( f->f_choice ) {
	case LDAP_FILTER_AND:
	case LDAP_FILTER_NOT:
	case LDAP_FILTER_OR: {
		int rc;


		for ( f = f->f_list; f != NULL; f = f->f_next ) {
			rc = slapi_filter_apply( f, fn, arg, error_code );
			if ( rc != 0 ) {
				return rc;
			}
			if ( *error_code == SLAPI_FILTER_SCAN_NOMORE ) {
				break;
			}
		}
		break;
	}
	case LDAP_FILTER_EQUALITY:
	case LDAP_FILTER_SUBSTRINGS:
	case LDAP_FILTER_GE:
	case LDAP_FILTER_LE:
	case LDAP_FILTER_PRESENT:
	case LDAP_FILTER_APPROX:
	case LDAP_FILTER_EXT:
		*error_code = fn( f, arg );
		break;
	default:
		*error_code = SLAPI_FILTER_UNKNOWN_FILTER_TYPE;
	}

	if ( *error_code == SLAPI_FILTER_SCAN_NOMORE ||
	     *error_code == SLAPI_FILTER_SCAN_CONTINUE ) {
		return 0;
	}

	return -1;
}
