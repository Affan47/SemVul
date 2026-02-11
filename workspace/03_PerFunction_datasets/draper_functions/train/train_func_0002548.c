slapi_filter_apply( struct slapi_filter *f, FILTER_APPLY_FN fn, void *arg,
					int *error_code)
{
	int rc = SLAPI_FILTER_SCAN_ERROR;

    if ( f == NULL ) {
	return SLAPI_FILTER_SCAN_NOMORE;
    }

    switch ( f->f_choice ) {
    case LDAP_FILTER_GE:
    case LDAP_FILTER_LE:
    case LDAP_FILTER_APPROX:
    case LDAP_FILTER_EQUALITY:
	rc = (*fn)(f, arg );
	break;
    case LDAP_FILTER_SUBSTRINGS:
	rc = (*fn)(f, arg);

	break;
    case LDAP_FILTER_PRESENT:
	rc = (*fn)(f, arg);
	break;
    case LDAP_FILTER_EXTENDED:
	rc = (*fn)(f, arg);
	break;
    case LDAP_FILTER_AND:
	rc = filter_apply_list( f->f_and, fn, arg, error_code );
	break;
    case LDAP_FILTER_OR:
	rc = filter_apply_list( f->f_or, fn, arg, error_code );
	break;
    case LDAP_FILTER_NOT:
	rc = filter_apply_list( f->f_not, fn, arg, error_code );
	break;
    default:

	*error_code = SLAPI_FILTER_UNKNOWN_FILTER_TYPE;
	rc = SLAPI_FILTER_SCAN_ERROR;
    }


	if (rc != SLAPI_FILTER_SCAN_ERROR && rc != SLAPI_FILTER_SCAN_STOP) {
		rc = SLAPI_FILTER_SCAN_NOMORE;
	}

	return(rc);
}
