igb_open ( struct net_device *netdev )
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	int err;

	DBGP ( "igb_open\n" );


	err = igb_setup_tx_resources ( adapter );
	if ( err ) {
		DBG ( "Error setting up TX resources!\n" );
		goto err_setup_tx;
	}


	err = igb_setup_rx_resources ( adapter );
	if ( err ) {
		DBG ( "Error setting up RX resources!\n" );
		goto err_setup_rx;
	}

	igb_configure_tx ( adapter );

	igb_configure_rx ( adapter );

	DBG ( "E1000_RXDCTL(0): %#08x\n",  E1000_READ_REG ( &adapter->hw, E1000_RXDCTL(0) ) );

	return 0;

err_setup_rx:
	DBG ( "err_setup_rx\n" );
	igb_free_tx_resources ( adapter );
err_setup_tx:
	DBG ( "err_setup_tx\n" );
	igb_reset ( adapter );

	return err;
}
