netdev_notify ( struct net_device *netdev ) {
	struct net_driver *driver;

	for_each_table_entry ( driver, NET_DRIVERS ) {
		if ( driver->notify )
			driver->notify ( netdev );
	}
}
