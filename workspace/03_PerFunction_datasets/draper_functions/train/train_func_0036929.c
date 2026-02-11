start_dhcp ( struct interface *job, struct net_device *netdev ) {
	struct dhcp_session *dhcp;
	int rc;


	get_cached_dhcpack();
	if ( fetch_uintz_setting ( NULL, &use_cached_setting ) ) {
		DBG ( "DHCP using cached network settings\n" );
		return 1;
	}


	dhcp = zalloc ( sizeof ( *dhcp ) );
	if ( ! dhcp )
		return -ENOMEM;
	ref_init ( &dhcp->refcnt, dhcp_free );
	intf_init ( &dhcp->job, &dhcp_job_desc, &dhcp->refcnt );
	intf_init ( &dhcp->xfer, &dhcp_xfer_desc, &dhcp->refcnt );
	timer_init ( &dhcp->timer, dhcp_timer_expired, &dhcp->refcnt );
	dhcp->netdev = netdev_get ( netdev );
	dhcp->local.sin_family = AF_INET;
	dhcp->local.sin_port = htons ( BOOTPC_PORT );
	dhcp->xid = random();


	dhcp_last_xid = dhcp->xid;


	if ( ( rc = xfer_open_socket ( &dhcp->xfer, SOCK_DGRAM, &dhcp_peer,
				  ( struct sockaddr * ) &dhcp->local ) ) != 0 )
		goto err;


	dhcp_set_state ( dhcp, &dhcp_state_discover );


	intf_plug_plug ( &dhcp->job, job );
	ref_put ( &dhcp->refcnt );
	return 0;

 err:
	dhcp_finished ( dhcp, rc );
	ref_put ( &dhcp->refcnt );
	return rc;
}
