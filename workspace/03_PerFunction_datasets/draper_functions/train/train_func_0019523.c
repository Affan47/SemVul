unregister_netdev ( struct net_device *netdev ) {


	netdev_close ( netdev );


	unregister_settings ( netdev_settings ( netdev ) );


	list_del ( &netdev->list );
	netdev_put ( netdev );
	DBGC ( netdev, "NETDEV %p unregistered\n", netdev );
}
