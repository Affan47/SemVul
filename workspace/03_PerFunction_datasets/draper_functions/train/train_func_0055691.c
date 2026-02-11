netdev_tx_defer ( struct net_device *netdev, struct io_buffer *iobuf ) {


	list_check_contains_entry ( iobuf, &netdev->tx_queue, list );


	list_del ( &iobuf->list );


	list_add_tail ( &iobuf->list, &netdev->tx_deferred );


	netdev_tx_err ( netdev, NULL, -ENOBUFS );
}
