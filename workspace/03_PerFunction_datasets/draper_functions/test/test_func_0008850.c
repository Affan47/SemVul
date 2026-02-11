dearmor_file( const char *fname )
{
    armor_filter_context_t afx;
    IOBUF inp = NULL, out = NULL;
    int rc = 0;
    int c;

    memset( &afx, 0, sizeof afx);


    inp = iobuf_open(fname);
    if (inp && is_secured_file (iobuf_get_fd (inp)))
      {
        iobuf_close (inp);
        inp = NULL;
        errno = EPERM;
      }
    if (!inp) {
	log_error(_("can't open `%s': %s\n"), fname? fname: "[stdin]",
					strerror(errno) );
	rc = G10ERR_OPEN_FILE;
	goto leave;
    }

    iobuf_push_filter( inp, armor_filter, &afx );

    if( (rc = open_outfile( fname, 0, &out )) )
	goto leave;


    while( (c = iobuf_get(inp)) != -1 )
	iobuf_put( out, c );


  leave:
    if( rc )
	iobuf_cancel(out);
    else
	iobuf_close(out);
    iobuf_close(inp);
    return rc;
}
