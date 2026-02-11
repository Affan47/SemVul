entry2reple( Slapi_Entry *e, Slapi_Entry *oe, int optype )
{
    char		*p, *estr;
    struct berval	*vals[ 2 ];
    struct berval	val;
    int			len;

    vals[ 0 ] = &val;
    vals[ 1 ] = NULL;


    if ( optype == OP_ADD ) {
    	val.bv_val = "add";
    	val.bv_len = 3;
    } else if ( optype == OP_DELETE) {
    	val.bv_val = "delete";
    	val.bv_len = 6;
    } else {
	return (1);
    }
    slapi_entry_add_values( e, attr_changetype, vals );

    estr = slapi_entry2str( oe, &len );
    p = estr;

    while (( p = strchr( p, '\n' )) != NULL ) {
	p++;
	if ( !ldap_utf8isspace( p )) {
	    break;
	}
    }
    val.bv_val = p;
    val.bv_len = len - ( p - estr );
    slapi_entry_add_values( e, attr_changes, vals );
    slapi_ch_free_string( &estr );
    return 0;
}
