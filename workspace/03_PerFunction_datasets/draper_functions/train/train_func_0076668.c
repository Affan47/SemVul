utf82u_strlen(const char *utf8_str) {

    int ch;
    int len = 0;

    while ( (ch = utf8_ildb(&utf8_str))>0 )
	if ( ch>0x10000 )
	    len += 2;
	else
	    ++len;
return( len );
}
