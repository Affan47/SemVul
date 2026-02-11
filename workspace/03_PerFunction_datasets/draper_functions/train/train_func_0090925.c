slapi_filter_get_attribute_type( Slapi_Filter *f, char **type )
{

    if ( f == NULL ) {
		return -1;
    }

    switch ( f->f_choice ) {
    case LDAP_FILTER_GE:
    case LDAP_FILTER_LE:
    case LDAP_FILTER_APPROX:
    case LDAP_FILTER_EQUALITY:
		*type = f->f_ava.ava_type;
	break;
    case LDAP_FILTER_SUBSTRINGS:
		*type = f->f_sub_type;
	break;
    case LDAP_FILTER_PRESENT:
 		*type = f->f_type;
	break;
    case LDAP_FILTER_EXTENDED:
		*type = f->f_mr_type;
	break;
    case LDAP_FILTER_AND:
    case LDAP_FILTER_OR:
    case LDAP_FILTER_NOT:
		return(-1);
    default:

		return -1;
    }


	return(0);
}
