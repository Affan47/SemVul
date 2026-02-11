tcp_open ( struct xfer_interface *xfer, struct sockaddr *peer,
		      struct sockaddr *local ) {
	struct sockaddr_tcpip *st_peer = ( struct sockaddr_tcpip * ) peer;
	struct sockaddr_tcpip *st_local = ( struct sockaddr_tcpip * ) local;
	struct tcp_connection *tcp;
	unsigned int bind_port;
	int rc;


	tcp = zalloc ( sizeof ( *tcp ) );
	if ( ! tcp )
		return -ENOMEM;
	DBGC ( tcp, "TCP %p allocated\n", tcp );
	xfer_init ( &tcp->xfer, &tcp_xfer_operations, &tcp->refcnt );
	tcp->prev_tcp_state = TCP_CLOSED;
	tcp->tcp_state = TCP_STATE_SENT ( TCP_SYN );
	tcp_dump_state ( tcp );
	tcp->snd_seq = random();
	INIT_LIST_HEAD ( &tcp->queue );
	tcp->timer.expired = tcp_expired;
	memcpy ( &tcp->peer, st_peer, sizeof ( tcp->peer ) );


	bind_port = ( st_local ? st_local->st_port : 0 );
	if ( ( rc = tcp_bind ( tcp, bind_port ) ) != 0 )
		goto err;


	start_timer_nodelay ( &tcp->timer );


	xfer_plug_plug ( &tcp->xfer, xfer );
	list_add ( &tcp->list, &tcp_conns );
	return 0;

 err:
	ref_put ( &tcp->refcnt );
	return rc;
}
