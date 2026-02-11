verify_one_file( const char *name )
{
    IOBUF fp;
    armor_filter_context_t afx;
    progress_filter_context_t pfx;
    int rc;

    print_file_status( STATUS_FILE_START, name, 1 );
    fp = iobuf_open(name);
    if (fp)
      iobuf_ioctl (fp,3,1,NULL);
    if (fp && is_secured_file (iobuf_get_fd (fp)))
      {
        iobuf_close (fp);
        fp = NULL;
        errno = EPERM;
      }
    if( !fp ) {
	print_file_status( STATUS_FILE_ERROR, name, 1 );
	log_error(_("can't open `%s'\n"), print_fname_stdin(name));
	return G10ERR_OPEN_FILE;
    }
    handle_progress (&pfx, fp, name);

    if( !opt.no_armor ) {
	if( use_armor_filter( fp ) ) {
	    memset( &afx, 0, sizeof afx);
	    iobuf_push_filter( fp, armor_filter, &afx );
	}
    }

    rc = proc_signature_packets( NULL, fp, NULL, name );
    iobuf_close(fp);
    write_status( STATUS_FILE_DONE );
    reset_literals_seen();
    return rc;
}
