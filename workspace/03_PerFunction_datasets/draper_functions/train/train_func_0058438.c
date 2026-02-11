e1000_poll ( struct net_device *netdev )
{
	struct e1000_adapter *adapter = netdev_priv( netdev );
	struct e1000_hw *hw = &adapter->hw;

	uint32_t icr;
	uint32_t tx_status;
	uint32_t rx_status;
	uint32_t rx_len;
	uint32_t rx_err;
	struct e1000_tx_desc *tx_curr_desc;
	struct e1000_rx_desc *rx_curr_desc;
	uint32_t i;

	DBGP ( "e1000_poll\n" );


	icr = E1000_READ_REG ( hw, ICR );
	if ( ! icr )
		return;

        DBG ( "e1000_poll: intr_status = %#08x\n", icr );


	while ( ( i = adapter->tx_head ) != adapter->tx_tail ) {

		tx_curr_desc = ( void * )  ( adapter->tx_base ) +
					   ( i * sizeof ( *adapter->tx_base ) );

		tx_status = tx_curr_desc->upper.data;


		if ( ! ( tx_status & E1000_TXD_STAT_DD ) )
			break;

		DBG ( "Sent packet. tx_head: %d tx_tail: %d tx_status: %#08x\n",
	    	      adapter->tx_head, adapter->tx_tail, tx_status );

		if ( tx_status & ( E1000_TXD_STAT_EC | E1000_TXD_STAT_LC |
				   E1000_TXD_STAT_TU ) ) {
			netdev_tx_complete_err ( netdev, adapter->tx_iobuf[i], -EINVAL );
			DBG ( "Error transmitting packet, tx_status: %#08x\n",
			      tx_status );
		} else {
			netdev_tx_complete ( netdev, adapter->tx_iobuf[i] );
			DBG ( "Success transmitting packet, tx_status: %#08x\n",
			      tx_status );
		}


		adapter->tx_fill_ctr--;
		memset ( tx_curr_desc, 0, sizeof ( *tx_curr_desc ) );

		adapter->tx_head = ( adapter->tx_head + 1 ) % NUM_TX_DESC;
	}


	while ( 1 ) {

		i = adapter->rx_curr;

		rx_curr_desc = ( void * )  ( adapter->rx_base ) +
			          ( i * sizeof ( *adapter->rx_base ) );
		rx_status = rx_curr_desc->status;

		DBG2 ( "Before DD Check RX_status: %#08x\n", rx_status );

		if ( ! ( rx_status & E1000_RXD_STAT_DD ) )
			break;

		if ( adapter->rx_iobuf[i] == NULL )
			break;

		DBG ( "RCTL = %#08x\n", E1000_READ_REG ( &adapter->hw, RCTL ) );

		rx_len = rx_curr_desc->length;

                DBG ( "Received packet, rx_curr: %d  rx_status: %#08x  rx_len: %d\n",
                      i, rx_status, rx_len );

                rx_err = rx_curr_desc->errors;

		iob_put ( adapter->rx_iobuf[i], rx_len );

		if ( rx_err & E1000_RXD_ERR_FRAME_ERR_MASK ) {

			netdev_rx_err ( netdev, adapter->rx_iobuf[i], -EINVAL );
			DBG ( "e1000_poll: Corrupted packet received!"
			      " rx_err: %#08x\n", rx_err );
		} else 	{

			netdev_rx ( netdev, adapter->rx_iobuf[i] );
		}
		adapter->rx_iobuf[i] = NULL;

		memset ( rx_curr_desc, 0, sizeof ( *rx_curr_desc ) );

		adapter->rx_curr = ( adapter->rx_curr + 1 ) % NUM_RX_DESC;
	}
	e1000_refill_rx_ring(adapter);
}
