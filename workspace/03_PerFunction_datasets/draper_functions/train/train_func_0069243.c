send_error_tail( void )
    {
    char buf[500];
    int buflen;

    if ( match( "**MSIE**", useragent ) )
	{
	int n;
	buflen = snprintf( buf, sizeof(buf), "<!--\n" );
	add_to_response( buf, buflen );
	for ( n = 0; n < 6; ++n )
	    {
	    buflen = snprintf( buf, sizeof(buf), "Padding so that MSIE deigns to show this error instead of its own canned one.\n" );
	    add_to_response( buf, buflen );
	    }
	buflen = snprintf( buf, sizeof(buf), "-->\n" );
	add_to_response( buf, buflen );
	}

    buflen = snprintf( buf, sizeof(buf), "\
<HR>\n\
<ADDRESS><A HREF=\"%s\">%s</A></ADDRESS>\n\
</BODY>\n\
</HTML>\n",
	SERVER_URL, SERVER_SOFTWARE );
    add_to_response( buf, buflen );
    }
