ftp_data_closed ( struct ftp_request *ftp, int rc ) {

	DBGC ( ftp, "FTP %p data connection closed: %s\n",
	       ftp, strerror ( rc ) );


	if ( rc ) {
		ftp_done ( ftp, rc );
	} else {
		ftp_next_state ( ftp );
	}
}
