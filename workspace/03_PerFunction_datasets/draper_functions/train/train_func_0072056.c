xml_free( xml *x )
{
	if ( x->tag ) {
		newstr_free( x->tag );
		free( x->tag );
	}
	if ( x->value ) {
		newstr_free( x->value );
		free( x->value );
	}
	if ( x->a ) {
		xmlattrib_free( x->a );
		free( x->a );
	}
	if ( x->down ) xml_free( x->down );
	if ( x->next ) xml_free( x->next );
}
