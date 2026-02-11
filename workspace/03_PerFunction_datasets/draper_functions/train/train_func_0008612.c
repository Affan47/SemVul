slam_open ( struct interface *xfer, struct uri *uri ) {
	static const struct sockaddr_in default_multicast = {
		.sin_family = AF_INET,
		.sin_port = htons ( SLAM_DEFAULT_MULTICAST_PORT ),
		.sin_addr = { htonl ( SLAM_DEFAULT_MULTICAST_IP ) },
	};
	struct slam_request *slam;
	struct sockaddr_tcpip server;
	struct sockaddr_in multicast;
	int rc;


	if ( ! uri->host )
		return -EINVAL;


	slam = zalloc ( sizeof ( *slam ) );
	if ( ! slam )
		return -ENOMEM;
	ref_init ( &slam->refcnt, slam_free );
	intf_init ( &slam->xfer, &slam_xfer_desc, &slam->refcnt );
	intf_init ( &slam->socket, &slam_socket_desc, &slam->refcnt );
	intf_init ( &slam->mc_socket, &slam_mc_socket_desc, &slam->refcnt );
	timer_init ( &slam->master_timer, slam_master_timer_expired,
		     &slam->refcnt );
	timer_init ( &slam->slave_timer, slam_slave_timer_expired,
		     &slam->refcnt );

	slam->header_len = 1;

	slam->num_blocks = 1;
	if ( ( rc = bitmap_resize ( &slam->bitmap, 1 ) ) != 0 ) {
		DBGC ( slam, "SLAM %p could not allocate initial bitmap: "
		       "%s\n", slam, strerror ( rc ) );
		goto err;
	}


	memset ( &server, 0, sizeof ( server ) );
	server.st_port = htons ( uri_port ( uri, SLAM_DEFAULT_PORT ) );
	if ( ( rc = xfer_open_named_socket ( &slam->socket, SOCK_DGRAM,
					     ( struct sockaddr * ) &server,
					     uri->host, NULL ) ) != 0 ) {
		DBGC ( slam, "SLAM %p could not open unicast socket: %s\n",
		       slam, strerror ( rc ) );
		goto err;
	}


	memcpy ( &multicast, &default_multicast, sizeof ( multicast ) );
	if ( uri->path &&
	     ( ( rc = slam_parse_multicast_address ( slam, uri->path,
						     &multicast ) ) != 0 ) ) {
		goto err;
	}
	if ( ( rc = xfer_open_socket ( &slam->mc_socket, SOCK_DGRAM,
				 ( struct sockaddr * ) &multicast,
				 ( struct sockaddr * ) &multicast ) ) != 0 ) {
		DBGC ( slam, "SLAM %p could not open multicast socket: %s\n",
		       slam, strerror ( rc ) );
		goto err;
	}


	start_timer_fixed ( &slam->slave_timer, SLAM_SLAVE_TIMEOUT );


	intf_plug_plug ( &slam->xfer, xfer );
	ref_put ( &slam->refcnt );
	return 0;

 err:
	slam_finished ( slam, rc );
	ref_put ( &slam->refcnt );
	return rc;
}
