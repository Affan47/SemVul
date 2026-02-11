netdev_close ( struct net_device *netdev ) {


	if ( ! ( netdev->state & NETDEV_OPEN ) )
		return;

	DBGC ( netdev, "NETDEV %s closing\n", netdev->name );


	list_del ( &netdev->open_list );


	netdev->state &= ~NETDEV_OPEN;


	netdev_notify ( netdev );


	netdev->op->close ( netdev );


	netdev_tx_flush ( netdev );
	netdev_rx_flush ( netdev );
}
