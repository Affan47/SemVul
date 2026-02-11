phantom_refill_rx_ring ( struct net_device *netdev ) {
	struct phantom_nic *phantom = netdev_priv ( netdev );
	struct io_buffer *iobuf;
	struct phantom_rds rds;
	unsigned int handle;
	int index;

	for ( handle = 0 ; handle < PHN_RDS_MAX_FILL ; handle++ ) {


		if ( phantom->rds_iobuf[handle] != NULL )
			continue;


		index = phantom_alloc_rds ( phantom );
		assert ( PHN_RDS_MAX_FILL < PHN_NUM_RDS );
		assert ( index >= 0 );


		iobuf = alloc_iob ( PHN_RX_BUFSIZE );
		if ( ! iobuf ) {

			netdev_rx_err ( netdev, NULL, -ENOMEM );
			break;
		}


		memset ( &rds, 0, sizeof ( rds ) );
		NX_FILL_2 ( &rds, 0,
			    handle, handle,
			    length, iob_len ( iobuf ) );
		NX_FILL_1 ( &rds, 1,
			    dma_addr, virt_to_bus ( iobuf->data ) );


		assert ( phantom->rds_iobuf[handle] == NULL );
		phantom->rds_iobuf[handle] = iobuf;


		phantom_post_rds ( phantom, &rds );
	}
}
