process_bibtexid( char *p, newstr *data )
{
	newstr tmp;
	char *start_p = p;
	newstr_init( &tmp );
	newstr_empty( data );

	while ( *p && *p!=',' ) newstr_addchar( &tmp, *p++ );
	if ( *p==',' ) p++;
	p = skip_ws( p );

	if ( tmp.len ) {
		if ( strchr( tmp.data, '=' ) ) {


			p = start_p;
		} else {

			newstr_addchar( data, '{' );
			newstr_strcat( data, tmp.data );
			newstr_addchar( data, '}' );
		}
	}

	newstr_free( &tmp );
	return p;
}
