attrlist_find(Slapi_Attr *a, const char *type)
{
	for ( ; a != NULL; a = a->a_next ) {
		if ( strcasecmp( a->a_type, type ) == 0 ) {
			return( a );
		}
	}

	return( NULL );
}
