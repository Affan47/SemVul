hermon_eth_transmit ( struct net_device *netdev,
				 struct io_buffer *iobuf ) {
	struct hermon_port *port = netdev->priv;
	struct ib_device *ibdev = port->ibdev;
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	int rc;


	if ( ( rc = ib_post_send ( ibdev, port->eth_qp, NULL,
				   iobuf ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p port %d could not transmit: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		return rc;
	}

	return 0;
}
