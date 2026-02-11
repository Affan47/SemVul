passthru_strs2bervals( char **ss )
{
    int			i;
    struct berval	**bvs;

    if ( ss == NULL || ss[0] == NULL ) {
	return( NULL );
    }

    for ( i = 0; ss[i] != NULL; ++i ) {
	;
    }

    bvs = (struct berval **)slapi_ch_calloc( i + 1, sizeof( struct berval * ));
    for ( i = 0; ss[i] != NULL; ++i ) {
	bvs[i] = (struct berval *)slapi_ch_malloc( sizeof( struct berval ));
	bvs[i]->bv_val = slapi_ch_strdup( ss[i] );
	bvs[i]->bv_len = strlen( ss[i] );
    }

    return( bvs );
}
