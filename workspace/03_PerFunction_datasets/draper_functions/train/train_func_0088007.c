wild_match( char* pat, char* str )
{
    int num = 1, last = 0, first = 1;
    char* term = NULL , *ptr = pat, *pos = str;

    do {
	term = ptr; ptr = strchr( ptr, '*' );
	if ( ptr ) { *ptr = '\0'; ptr++; }
	else { last = 1; }

	if ( *term != '\0' ) {
	    if ( first ) {
		if ( strncmp( pos, term, strlen( term ) ) != 0 ) {
		    return 0;
		}
		pos += strlen( term );
	    } else if ( !first ) {
		if ( last ) {
		    pos = strrstr( pos, term );
		} else {
		    pos = strstr( pos, term );
		}
		if ( pos == 0 ) { return 0; }
		pos += strlen( term );
	    }
	    if ( last && *pos != '\0' ) {
		return 0;
	    }
	}

	num++; first = 0;
    } while ( term && !last );

    return 1;
}
