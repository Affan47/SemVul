myri10ge_interrupt_handler ( struct net_device *netdev )
{
	struct myri10ge_private *priv;
	mcp_irq_data_t		*irq_data;
	uint8			 valid;

	priv = myri10ge_priv ( netdev );
	irq_data = &priv->dma->irq_data;


	rmb();
	valid = irq_data->valid;
	if ( !valid )
		return;
	DBG2 ( "irq " );


	*priv->irq_deassert = 0;
	mb();


	if ( valid & 1 ) {


		DBG2 ( "rx " );
		*priv->irq_claim = htonl ( 3 );
		wmb();
	}


	if ( valid & 2 ) {
		unsigned int nic_done_count;

		DBG2 ( "snt " );
		nic_done_count = ntohl ( priv->dma->irq_data.send_done_count );
		while ( priv->transmits_done != nic_done_count ) {
			struct io_buffer *iob;

			iob = priv->transmit_iob [priv->transmits_done
						  & MYRI10GE_TRANSMIT_WRAP];
			DBG2 ( "%p ", iob );
			netdev_tx_complete ( netdev, iob );
			++priv->transmits_done;
		}
	}


	if ( irq_data->stats_updated ) {


		DBG2 ( "stats " );
		if ( ntohl ( irq_data->link_up ) == MXGEFW_LINK_UP )
			netdev_link_up ( netdev );
		else
			netdev_link_down ( netdev );


	}


	DBG2 ( "wait " );
	do {
		mb();
	} while ( irq_data->valid );


	DBG2 ( "claim\n" );
	* ( priv->irq_claim + 1 ) = htonl ( 3 );
	mb();
}
