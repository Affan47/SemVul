do_cancel( Plustek_Scanner *scanner, SANE_Bool closepipe  )
{
	struct SIGACTION act;
	SANE_Pid         res;
	short            int_cnt;

	DBG( _DBG_PROC,"do_cancel\n" );

	scanner->scanning = SANE_FALSE;

	if( scanner->reader_pid != -1 ) {

		DBG( _DBG_PROC, ">>>>>>>> killing reader_process <<<<<<<<\n" );


		if( -1 != scanner->hw->fd ) {
			int_cnt = 1;
			scanner->hw->stopScan( scanner->hw, &int_cnt );
		}

	    sigemptyset(&(act.sa_mask));
    	act.sa_flags = 0;

		act.sa_handler = sigalarm_handler;
		sigaction( SIGALRM, &act, 0 );


		sanei_thread_kill( scanner->reader_pid );


		alarm(10);
		res = sanei_thread_waitpid( scanner->reader_pid, 0 );
		alarm(0);

		if( res != scanner->reader_pid ) {
			DBG( _DBG_PROC,"sanei_thread_waitpid() failed !\n");


#ifdef USE_PTHREAD
			sanei_thread_kill( scanner->reader_pid );
#else
			sanei_thread_sendsig( scanner->reader_pid, SIGKILL );
#endif
		}

		scanner->reader_pid = -1;
		DBG( _DBG_PROC,"reader_process killed\n");
	}

	if( SANE_TRUE == closepipe ) {
		close_pipe( scanner );
	}

	drvclose( scanner->hw );

	if( tsecs != 0 ) {
		DBG( _DBG_INFO, "TIME END 2: %lus\n", time(NULL)-tsecs);
		tsecs = 0;
	}

	return SANE_STATUS_CANCELLED;
}
