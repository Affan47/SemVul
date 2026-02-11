open_sigfile( const char *iname, progress_filter_context_t *pfx )
{
    IOBUF a = NULL;
    size_t len;

    if( !iobuf_is_pipe_filename (iname) ) {
	len = strlen(iname);
	if( len > 4 && ( !strcmp(iname + len - 4, EXTSEP_S "sig")
                        || ( len > 5 && !strcmp(iname + len - 5, EXTSEP_S "sign") )
                        || !strcmp(iname + len - 4, EXTSEP_S "asc")) ) {
	    char *buf;
	    buf = xstrdup(iname);
	    buf[len-(buf[len-1]=='n'?5:4)] = 0 ;
	    a = iobuf_open( buf );
            if (a && is_secured_file (iobuf_get_fd (a)))
              {
                iobuf_close (a);
                a = NULL;
                errno = EPERM;
              }
	    if( a && opt.verbose )
		log_info(_("assuming signed data in `%s'\n"), buf );
	    if (a && pfx)
	      handle_progress (pfx, a, buf);
            xfree(buf);
	}
    }
    return a;
}
