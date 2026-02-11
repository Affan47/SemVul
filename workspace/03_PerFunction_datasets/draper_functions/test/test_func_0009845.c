slapi_ch_array_free( char **arrayp )
{
	char **p;

	if ( arrayp != NULL ) {
		for ( p = arrayp; *p != NULL; p++ ) {
			slapi_ch_free( (void **)p );
		}
		slapi_ch_free( (void **)&arrayp );
	}
}
