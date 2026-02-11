pcnet32_process_rx_packets ( struct net_device *netdev )
{
	struct pcnet32_private *priv = netdev_priv ( netdev );
	struct pcnet32_rx_desc *rx_curr_desc;
	u16 status;
	u32 len;
	int i;

	DBGP ( "pcnet32_process_rx_packets\n" );

	for ( i = 0; i < RX_RING_SIZE; i++ ) {
		rx_curr_desc = priv->rx_base + priv->rx_curr;

		status = le16_to_cpu ( rx_curr_desc->status );
		rmb();

		DBG ( "Before OWN bit check, status: %#08x\n", status );


		if ( status & DescOwn )
			break;


		if ( priv->rx_iobuf[priv->rx_curr] == NULL )
			break;

		DBG ( "Received packet.\n" );
		DBG ( "priv->rx_curr	= %d\n", priv->rx_curr );
		DBG ( "rx_len		= %d\n",
		      ( le32_to_cpu ( rx_curr_desc->msg_length ) & 0xfff ) - 4 );
		DBG ( "rx_curr_desc	= %#08lx\n",
		      virt_to_bus ( rx_curr_desc ) );


		if ( status & 0x4000 ) {
			netdev_rx_err ( netdev, priv->rx_iobuf[priv->rx_curr],
					-EINVAL );
			DBG ( "Corrupted packet received!\n");
		} else {

			len = ( le32_to_cpu ( rx_curr_desc->msg_length ) & 0xfff ) - 4;
			iob_put ( priv->rx_iobuf[priv->rx_curr], len );


			netdev_rx ( netdev, priv->rx_iobuf[priv->rx_curr] );
		}


		priv->rx_iobuf[priv->rx_curr] = NULL;
		memset ( rx_curr_desc, 0, sizeof(*rx_curr_desc) );


		priv->rx_curr = ( priv->rx_curr + 1 ) % RX_RING_SIZE;
	}


	pcnet32_refill_rx_ring ( priv );
}
