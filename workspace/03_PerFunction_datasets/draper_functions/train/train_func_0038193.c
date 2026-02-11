tftp_send_rrq ( struct tftp_request *tftp ) {
	struct tftp_rrq *rrq;
	const char *path;
	size_t len;
	struct io_buffer *iobuf;


	path = tftp->uri->path;
	if ( *path == '/' )
		path++;

	DBGC ( tftp, "TFTP %p requesting \"%s\"\n", tftp, path );


	len = ( sizeof ( *rrq ) + strlen ( path ) + 1
		+ 5 + 1
		+ 7 + 1 + 5 + 1
		+ 5 + 1 + 1 + 1
		+ 9 + 1 + 1  );
	iobuf = xfer_alloc_iob ( &tftp->socket, len );
	if ( ! iobuf )
		return -ENOMEM;


	rrq = iob_put ( iobuf, sizeof ( *rrq ) );
	rrq->opcode = htons ( TFTP_RRQ );
	iob_put ( iobuf, snprintf ( iobuf->tail, iob_tailroom ( iobuf ),
				    "%s%coctet", path, 0 ) + 1 );
	if ( tftp->flags & TFTP_FL_RRQ_SIZES ) {
		iob_put ( iobuf, snprintf ( iobuf->tail,
					    iob_tailroom ( iobuf ),
					    "blksize%c%d%ctsize%c0", 0,
					    tftp_request_blksize, 0, 0 ) + 1 );
	}
	if ( tftp->flags & TFTP_FL_RRQ_MULTICAST ) {
		iob_put ( iobuf, snprintf ( iobuf->tail,
					    iob_tailroom ( iobuf ),
					    "multicast%c", 0 ) + 1 );
	}


	return xfer_deliver_iob ( &tftp->socket, iobuf );
}
