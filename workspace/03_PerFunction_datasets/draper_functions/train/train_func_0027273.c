make_outfile_name( const char *iname )
{
    size_t n;

    if ( iobuf_is_pipe_filename (iname) )
	return xstrdup("-");

    n = strlen(iname);
    if( n > 4 && (    !CMP_FILENAME(iname+n-4, EXTSEP_S "gpg")
		   || !CMP_FILENAME(iname+n-4, EXTSEP_S "pgp")
		   || !CMP_FILENAME(iname+n-4, EXTSEP_S "sig")
		   || !CMP_FILENAME(iname+n-4, EXTSEP_S "asc") ) ) {
	char *buf = xstrdup( iname );
	buf[n-4] = 0;
	return buf;
    }
    else if( n > 5 && !CMP_FILENAME(iname+n-5, EXTSEP_S "sign") ) {
	char *buf = xstrdup( iname );
	buf[n-5] = 0;
	return buf;
    }

    log_info(_("%s: unknown suffix\n"), iname );
    return NULL;
}
