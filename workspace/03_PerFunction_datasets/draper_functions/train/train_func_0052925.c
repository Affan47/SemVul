ifec_rx_process ( struct net_device *netdev )
{
	struct ifec_private *priv   = netdev->priv;
	int cur_rx = priv->cur_rx;
	struct io_buffer *iob = priv->rx_iobs[cur_rx];
	struct ifec_rfd *rfd = priv->rfds[cur_rx];
	unsigned int rx_len;
	s16 status;

	DBGP ( "ifec_rx_process\n" );


	while ( iob && rfd && ( status = rfd->status ) ) {
		rx_len = rfd->count & RFDMaskCount;

		DBG2 ( "Got a packet: Len = %d, cur_rx = %d.\n", rx_len,
		       cur_rx );
		DBGIO_HD ( (void*)rfd->packet, 0x30 );

		if ( ( status & ( RFD_STATUS & ~RFDShort ) ) != RFD_OK ) {
			DBG ( "Corrupted packet received. "
			      "Status = %#08hx\n", status );
			netdev_rx_err ( netdev, iob, -EINVAL );
		} else {

			iob_put ( iob, rx_len );
			DBG2 ( "Received packet: %p, len: %d\n", iob, rx_len );
			netdev_rx ( netdev, iob );
		}


		priv->rx_iobs[cur_rx] = NULL;
		priv->rfds[cur_rx] = NULL;


		priv->cur_rx = ( cur_rx + 1 ) % RFD_COUNT;
		cur_rx = priv->cur_rx;
		iob = priv->rx_iobs[cur_rx];
		rfd = priv->rfds[cur_rx];
	}

	ifec_refill_rx_ring ( netdev );
}
