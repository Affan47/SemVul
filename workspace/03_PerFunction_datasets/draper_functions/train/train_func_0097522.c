pxenv_tftp_open ( struct s_PXENV_TFTP_OPEN *tftp_open ) {
	int rc;

	DBG ( "PXENV_TFTP_OPEN" );


	pxe_tftp_close ( 0 );


	if ( ( rc = pxe_tftp_open ( tftp_open->ServerIPAddress,
				    tftp_open->TFTPPort,
				    tftp_open->FileName,
				    tftp_open->PacketSize,
				    0) ) != 0 ) {
		tftp_open->Status = PXENV_STATUS ( rc );
		return PXENV_EXIT_FAILURE;
	}


	while ( ( ( rc = pxe_tftp.rc ) == -EINPROGRESS ) &&
		( pxe_tftp.max_offset == 0 ) ) {
		step();
	}
	pxe_tftp.blksize = xfer_window ( &pxe_tftp.xfer );
	tftp_open->PacketSize = pxe_tftp.blksize;
	DBG ( " blksize=%d", tftp_open->PacketSize );


	if ( rc == -EINPROGRESS )
		rc = 0;

	tftp_open->Status = PXENV_STATUS ( rc );
	return ( rc ? PXENV_EXIT_FAILURE : PXENV_EXIT_SUCCESS );
}
