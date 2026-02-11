copyparse(char *str) {
    char *ret, *rpt;
    int ch,i;

    if ( str==NULL )
return( str );

    rpt=ret=galloc(strlen(str)+1);
    while ( *str ) {
	if ( *str=='\\' ) {
	    ++str;
	    if ( *str=='n' ) ch = '\n';
	    else if ( *str=='r' ) ch = '\r';
	    else if ( *str=='t' ) ch = '\t';
	    else if ( *str=='b' ) ch = '\b';
	    else if ( *str=='f' ) ch = '\f';
	    else if ( *str=='\\' ) ch = '\\';
	    else if ( *str=='(' ) ch = '(';
	    else if ( *str==')' ) ch = ')';
	    else if ( *str>='0' && *str<='7' ) {
		for ( i=ch = 0; i<3 && *str>='0' && *str<='7'; ++i )
		    ch = (ch<<3) + *str++-'0';
		--str;
	    } else
		ch = *str;
	    ++str;
	    *rpt++ = ch;
	} else
	    *rpt++ = *str++;
    }
    *rpt = '\0';
    if ( !utf8_valid(ret)) {

	rpt = latin1_2_utf8_copy(ret);
	free(ret);
	ret = rpt;
    }
    if ( !AllAscii(ret)) {
	rpt = StripToASCII(ret);
	free(ret);
	ret = rpt;
    }
return(ret);
}
