net_tx ( struct io_buffer *iobuf, struct net_device *netdev,
	     struct net_protocol *net_protocol, const void *ll_dest ) {
	struct ll_protocol *ll_protocol = netdev->ll_protocol;
	int rc;


	netdev_poll ( netdev );


	if ( ( rc = ll_protocol->push ( netdev, iobuf, ll_dest, netdev->ll_addr,
					net_protocol->net_proto ) ) != 0 ) {
		free_iob ( iobuf );
		return rc;
	}


	return netdev_tx ( netdev, iobuf );
}
