netdev_poll ( struct net_device *netdev ) {

	if ( netdev_is_open ( netdev ) )
		netdev->op->poll ( netdev );
}
