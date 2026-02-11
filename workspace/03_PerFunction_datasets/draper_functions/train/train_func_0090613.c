reader_process( void *args )
{
	int              line;
	unsigned char   *buf;
	unsigned long    data_length;
	struct SIGACTION act;
	sigset_t         ignore_set;
	SANE_Status      status;

	U12_Scanner *scanner = (U12_Scanner *)args;

	if( sanei_thread_is_forked()) {
		DBG( _DBG_PROC, "reader_process started (forked)\n" );
		close( scanner->r_pipe );
		scanner->r_pipe = -1;
	} else {
		DBG( _DBG_PROC, "reader_process started (as thread)\n" );
	}

	sigfillset ( &ignore_set );
	sigdelset  ( &ignore_set, SIGTERM );
#if defined (__APPLE__) && defined (__MACH__)
	sigdelset  ( &ignore_set, SIGUSR2 );
#endif
	sigprocmask( SIG_SETMASK, &ignore_set, 0 );

	cancelRead = SANE_FALSE;


	memset( &act, 0, sizeof (act));
	sigemptyset(&(act.sa_mask));
	act.sa_flags = 0;

	act.sa_handler = reader_process_sigterm_handler;
	sigaction( SIGTERM, &act, 0 );

	act.sa_handler = usb_reader_process_sigterm_handler;
	sigaction( SIGUSR1, &act, 0 );

	data_length = scanner->params.lines * scanner->params.bytes_per_line;

	DBG( _DBG_PROC, "reader_process:"
					"starting to READ data (%lu bytes)\n", data_length );
	DBG( _DBG_PROC, "buf = 0x%08lx\n", (unsigned long)scanner->buf );

	if( NULL == scanner->buf ) {
		DBG( _DBG_FATAL, "NULL Pointer !!!!\n" );
		return SANE_STATUS_IO_ERROR;
	}


	buf    = scanner->buf;
	status = u12if_prepare( scanner->hw );

	if( SANE_STATUS_GOOD == status ) {

		for( line = 0; line < scanner->params.lines; line++ ) {

			status = u12if_readLine( scanner->hw, buf );
			if( SANE_STATUS_GOOD != status ) {
				break;
			}

			write( scanner->w_pipe, buf, scanner->params.bytes_per_line );
    		buf += scanner->params.bytes_per_line;
		}
	}

	close( scanner->w_pipe );
	scanner->w_pipe = -1;


	if( SANE_STATUS_GOOD != status ) {
		DBG( _DBG_ERROR, "read failed, status = %i\n", (int)status );
		return status;
	}

	DBG( _DBG_PROC, "reader_process: finished reading data\n" );
	return SANE_STATUS_GOOD;
}
