ftp_data_deliver_iob ( struct xfer_interface *data,
				  struct io_buffer *iobuf,
				  struct xfer_metadata *meta __unused ) {
	struct ftp_request *ftp =
		container_of ( data, struct ftp_request, data );
	int rc;

	if ( ( rc = xfer_deliver_iob ( &ftp->xfer, iobuf ) ) != 0 ) {
		DBGC ( ftp, "FTP %p failed to deliver data: %s\n",
		       ftp, strerror ( rc ) );
		return rc;
	}

	return 0;
}
