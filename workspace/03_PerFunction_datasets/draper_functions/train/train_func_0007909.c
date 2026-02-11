neighbour_discovered ( struct neighbour *neighbour,
				   const void *ll_dest ) {
	struct net_device *netdev = neighbour->netdev;
	struct ll_protocol *ll_protocol = netdev->ll_protocol;
	struct net_protocol *net_protocol = neighbour->net_protocol;
	struct io_buffer *iobuf;
	int rc;


	memcpy ( neighbour->ll_dest, ll_dest, ll_protocol->ll_addr_len );
	DBGC ( neighbour, "NEIGHBOUR %s %s %s is %s %s\n", netdev->name,
	       net_protocol->name, net_protocol->ntoa ( neighbour->net_dest ),
	       ll_protocol->name, ll_protocol->ntoa ( neighbour->ll_dest ) );


	stop_timer ( &neighbour->timer );


	ref_get ( &neighbour->refcnt );
	while ( ( iobuf = list_first_entry ( &neighbour->tx_queue,
					     struct io_buffer, list )) != NULL){
		DBGC2 ( neighbour, "NEIGHBOUR %s %s %s transmitting deferred "
			"packet\n", netdev->name, net_protocol->name,
			net_protocol->ntoa ( neighbour->net_dest ) );
		list_del ( &iobuf->list );
		if ( ( rc = net_tx ( iobuf, netdev, net_protocol, ll_dest,
				     netdev->ll_addr ) ) != 0 ) {
			DBGC ( neighbour, "NEIGHBOUR %s %s %s could not "
			       "transmit deferred packet: %s\n",
			       netdev->name, net_protocol->name,
			       net_protocol->ntoa ( neighbour->net_dest ),
			       strerror ( rc ) );

		}
	}
	ref_put ( &neighbour->refcnt );
}
