dsgw_rdn_values( char *dn )
{
    char	**rdns, **rdncomps, *val;
    int		i;

    if (( rdns = dsgw_ldap_explode_dn( dn, 0 )) == NULL ) {
	return( NULL );
    }

    rdncomps = dsgw_ldap_explode_rdn( rdns[0], 0 );
    dsgw_charray_free( rdns );
    if ( rdncomps == NULL ) {
	return( NULL );
    }

    for ( i = 0; rdncomps[ i ] != NULL; ++i ) {
	if (( val = strchr( rdncomps[ i ], '=' )) == NULL ) {
	    dsgw_charray_free( rdncomps );
	    return( NULL );
	}
	++val;
	strcpy_special_undo( val, val );
    }

    return( rdncomps );
}
