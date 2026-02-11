snpnet_complete ( struct net_device *netdev, void *txbuf ) {
	struct io_buffer *tmp;
	struct io_buffer *iobuf;

	list_for_each_entry_safe ( iobuf, tmp, &netdev->tx_queue, list ) {
		if ( iobuf->data == txbuf ) {
			netdev_tx_complete ( netdev, iobuf );
			break;
		}
	}
}
