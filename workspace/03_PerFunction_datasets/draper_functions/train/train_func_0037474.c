pxenv_file_select ( struct s_PXENV_FILE_SELECT *file_select ) {
	fd_set fdset;
	int ready;

	DBG ( "PXENV_FILE_SELECT %d", file_select->FileHandle );

	FD_ZERO ( &fdset );
	FD_SET ( file_select->FileHandle, &fdset );
	if ( ( ready = select ( &fdset, 0 ) ) < 0 ) {
		file_select->Status = PXENV_STATUS ( ready );
		return PXENV_EXIT_FAILURE;
	}

	file_select->Ready = ( ready ? RDY_READ : 0 );
	file_select->Status = PXENV_STATUS_SUCCESS;
	return PXENV_EXIT_SUCCESS;
}
