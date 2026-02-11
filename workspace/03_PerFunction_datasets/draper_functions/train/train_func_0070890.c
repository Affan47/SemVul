schema_strcmp( const char *s1, const char *s2 )
{
	if ( s1 == NULL ) {
		if ( s2 == NULL ) {
			return 0;
		}
		return -1;
	}

	if ( s2 == NULL ) {
		return 1;
	}

	return strcmp( s1, s2 );
}
