legacy_poll ( struct net_device *netdev ) {
	struct nic *nic = netdev->priv;
	struct io_buffer *iobuf;

	iobuf = alloc_iob ( ETH_FRAME_LEN );
	if ( ! iobuf )
		return;

	nic->packet = iobuf->data;
	if ( nic->nic_op->poll ( nic, 1 ) ) {
		DBG ( "Received %d bytes\n", nic->packetlen );
		iob_put ( iobuf, nic->packetlen );
		netdev_rx ( netdev, iobuf );
	} else {
		free_iob ( iobuf );
	}
}
