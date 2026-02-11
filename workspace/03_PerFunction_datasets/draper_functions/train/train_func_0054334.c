slapi_entry_first_attr( const Slapi_Entry *e, Slapi_Attr **attr )
{
	if ( e == NULL ) {
		return -1;
	}

	*attr = e->e_attrs;

	return ( *attr != NULL ) ? 0 : -1;
}
