ftp_open ( struct interface *xfer, struct uri *uri ) {
	struct ftp_request *ftp;
	struct sockaddr_tcpip server;
	int rc;


	if ( ! uri->path )
		return -EINVAL;
	if ( ! uri->host )
		return -EINVAL;


	ftp = zalloc ( sizeof ( *ftp ) );
	if ( ! ftp )
		return -ENOMEM;
	ref_init ( &ftp->refcnt, ftp_free );
	intf_init ( &ftp->xfer, &ftp_xfer_desc, &ftp->refcnt );
	intf_init ( &ftp->control, &ftp_control_desc, &ftp->refcnt );
	intf_init ( &ftp->data, &ftp_data_desc, &ftp->refcnt );
	ftp->uri = uri_get ( uri );
	ftp->recvbuf = ftp->status_text;
	ftp->recvsize = sizeof ( ftp->status_text ) - 1;

	DBGC ( ftp, "FTP %p fetching %s\n", ftp, ftp->uri->path );


	memset ( &server, 0, sizeof ( server ) );
	server.st_port = htons ( uri_port ( uri, FTP_PORT ) );
	if ( ( rc = xfer_open_named_socket ( &ftp->control, SOCK_STREAM,
					     ( struct sockaddr * ) &server,
					     uri->host, NULL ) ) != 0 )
		goto err;


	intf_plug_plug ( &ftp->xfer, xfer );
	ref_put ( &ftp->refcnt );
	return 0;

 err:
	DBGC ( ftp, "FTP %p could not create request: %s\n",
	       ftp, strerror ( rc ) );
	ftp_done ( ftp, rc );
	ref_put ( &ftp->refcnt );
	return rc;
}
