pnic_poll ( struct net_device *netdev ) {
	struct pnic *pnic = netdev->priv;
	struct io_buffer *iobuf;
	uint16_t length;
	uint16_t qlen;


	while ( 1 ) {
		if ( pnic_command ( pnic, PNIC_CMD_RECV_QLEN, NULL, 0,
				    &qlen, sizeof ( qlen ), NULL )
		     != PNIC_STATUS_OK )
			return;
		if ( qlen == 0 )
			return;
		iobuf = alloc_iob ( ETH_FRAME_LEN );
		if ( ! iobuf ) {
			DBG ( "could not allocate buffer\n" );
			netdev_rx_err ( netdev, NULL, -ENOMEM );
			return;
		}
		if ( pnic_command ( pnic, PNIC_CMD_RECV, NULL, 0,
				    iobuf->data, ETH_FRAME_LEN, &length )
		     != PNIC_STATUS_OK ) {
			netdev_rx_err ( netdev, iobuf, -EIO );
			return;
		}
		iob_put ( iobuf, length );
		netdev_rx ( netdev, iobuf );
	}
}
