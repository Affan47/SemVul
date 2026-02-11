skeleton_transmit ( struct net_device *netdev,
			       struct io_buffer *iobuf ) {
	struct skeleton_nic *skel = netdev->priv;

	DBGC ( skel, "SKELETON %p does not yet support transmit\n", skel );
	( void ) iobuf;
	return -ENOTSUP;
}
