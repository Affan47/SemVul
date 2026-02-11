slapi_filter_get_ava( struct slapi_filter *f, char **type, struct berval **bval )
{
	switch ( f->f_choice ) {
	  case LDAP_FILTER_EQUALITY:
	  case LDAP_FILTER_GE:
	  case LDAP_FILTER_LE:
	  case LDAP_FILTER_APPROX:
	    break;
	  default:
	    *type = NULL;
	    *bval = NULL;
	    return( -1 );
	}
	*type = f->f_avtype;
	*bval = &f->f_avvalue;
	return( 0 );
}
