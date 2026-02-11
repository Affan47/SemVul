an_find(
    AttributeName *a,
    struct berval *s
)
{
	if( a == NULL ) return 0;

	for ( ; a->an_name.bv_val; a++ ) {
		if ( a->an_name.bv_len != s->bv_len) continue;
		if ( strcasecmp( s->bv_val, a->an_name.bv_val ) == 0 ) {
			return( 1 );
		}
	}

	return( 0 );
}
