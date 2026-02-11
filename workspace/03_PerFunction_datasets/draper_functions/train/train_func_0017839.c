name_givennames_nosplit( char *start_first, char *end_first, newstr *outname )
{
	char *p;
	p = start_first;
	while ( p!=end_first ) {
		if ( !is_ws( *p ) && *p!='.' ) {
			p = name_addmultibytechar( outname, p, end_first );
		} else {
			if ( *p=='.' ) p++;
			while ( p!=end_first && is_ws( *p ) ) p++;
			if ( p!=end_first )
				newstr_addchar( outname, '|' );
		}
	}
}
