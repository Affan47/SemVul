next_token( char **sp )
{
    int		in_quote = 0;
    char	*p, *tokstart, *t;

    if ( **sp == '\0' ) {
	return( NULL );
    }

    p = *sp;

    while ( ldap_utf8isspace( p )) {
	++p;
    }

    if ( *p == '\0' ) {
	return( NULL );
    }

    if ( *p == '\"' ) {
	in_quote = 1;
	++p;
    }
    t = tokstart = p;

    for ( ;; ) {
	if ( *p == '\0' || ( ldap_utf8isspace( p ) && !in_quote )) {
	    if ( *p != '\0' ) {
		++p;
	    }
	    *t++ = '\0';
	    break;
	}

	if ( *p == '\"' ) {
	    in_quote = !in_quote;
	    ++p;
	} else {
	    *t++ = *p++;
	}
    }

    *sp = p;

    if ( t == tokstart ) {
	return( NULL );
    }

    return( dsgw_ch_strdup( tokstart ));
}
