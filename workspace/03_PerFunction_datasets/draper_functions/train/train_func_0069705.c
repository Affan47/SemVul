netdev_tx_complete_err ( struct net_device *netdev,
			      struct io_buffer *iobuf, int rc ) {


	list_check_contains_entry ( iobuf, &netdev->tx_queue, list );


	list_del ( &iobuf->list );
	netdev_tx_err ( netdev, iobuf, rc );


	if ( ( iobuf = list_first_entry ( &netdev->tx_deferred,
					  struct io_buffer, list ) ) != NULL ) {
		list_del ( &iobuf->list );
		netdev_tx ( netdev, iobuf );
	}
}
