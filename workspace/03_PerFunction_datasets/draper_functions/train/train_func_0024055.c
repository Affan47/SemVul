wrapLines( char *buf )
{
    char *src = buf;
    char *obuf, *dst;
    int lwidth = 0;

    obuf = malloc( strlen( buf ) * 2 );
    if ( obuf == NULL ) {
	return NULL;
    }
    dst = obuf;
    while ( *src != '\0' ) {
	if (( ++lwidth > 50 ) && isspace( *src )) {
	    *dst++ = '\\';
	    *dst++ = 'n';
	    lwidth = 0;
	    src++;
	} else {
	    *dst++ = *src++;
	}
    }
    *dst = '\0';
    return obuf;
}
