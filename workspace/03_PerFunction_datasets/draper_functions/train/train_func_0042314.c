do_dir( void )
    {
    char buf[10000];
    size_t buflen;
    char* contents;
    size_t contents_size, contents_len;
#ifdef HAVE_SCANDIR
    int n, i;
    struct dirent **dl;
    char* name_info;
#else
    char command[10000];
    FILE* fp;
#endif

    if ( pathinfo != (char*) 0 )
	send_error( 404, "Not Found", "", "File not found." );


    auth_check( file );


    check_referer();

#ifdef HAVE_SCANDIR
    n = scandir( file, &dl, NULL, alphasort );
    if ( n < 0 )
	{
	syslog(
	    LOG_INFO, "%.80s Directory \"%.80s\" is protected",
	    remote_addr, path );
	send_error( 403, "Forbidden", "", "Directory is protected." );
	}
#endif

    contents_size = 0;
    buflen = snprintf( buf, sizeof(buf), "\
<HTML>\n\
<HEAD><TITLE>Index of %s</TITLE></HEAD>\n\
<BODY BGCOLOR=\"#99cc99\" TEXT=\"#000000\" LINK=\"#2020ff\" VLINK=\"#4040cc\">\n\
<H4>Index of %s</H4>\n\
<PRE>\n",
	file, file );
    add_to_buf( &contents, &contents_size, &contents_len, buf, buflen );

#ifdef HAVE_SCANDIR

    for ( i = 0; i < n; ++i )
	{
	name_info = file_details( file, dl[i]->d_name );
	add_to_buf(
	    &contents, &contents_size, &contents_len, name_info,
	    strlen( name_info ) );
	}

#else

    if ( strchr( file, '\'' ) == (char*) 0 )
	{
	(void) snprintf(
	    command, sizeof(command),
	    "ls -lgF '%s' | tail +2 | sed -e 's/^\\([^ ][^ ]*\\)\\(  *[^ ][^ ]*  *[^ ][^ ]*  *[^ ][^ ]*\\)\\(  *[^ ][^ ]*\\)  *\\([^ ][^ ]*  *[^ ][^ ]*  *[^ ][^ ]*\\)  *\\(.*\\)$/\\1 \\3  \\4  |\\5/' -e '/ -> /!s,|\\([^*]*\\)$,|<A HREF=\"\\1\">\\1</A>,' -e '/ -> /!s,|\\(.*\\)\\([*]\\)$,|<A HREF=\"\\1\">\\1</A>\\2,' -e '/ -> /s,|\\([^@]*\\)\\(@* -> \\),|<A HREF=\"\\1\">\\1</A>\\2,' -e 's/|//'",
	    file );
	fp = popen( command, "r" );
	for (;;)
	    {
	    size_t r;
	    r = fread( buf, 1, sizeof(buf), fp );
	    if ( r == 0 )
		break;
	    add_to_buf( &contents, &contents_size, &contents_len, buf, r );
	    }
	(void) pclose( fp );
	}
#endif

    buflen = snprintf( buf, sizeof(buf), "\
</PRE>\n\
<HR>\n\
<ADDRESS><A HREF=\"%s\">%s</A></ADDRESS>\n\
</BODY>\n\
</HTML>\n",
	SERVER_URL, SERVER_SOFTWARE );
    add_to_buf( &contents, &contents_size, &contents_len, buf, buflen );

    add_headers( 200, "Ok", "", "", "text/html; charset=%s", contents_len, sb.st_mtime );
    if ( method != METHOD_HEAD )
	add_to_response( contents, contents_len );
    send_response();
    }
