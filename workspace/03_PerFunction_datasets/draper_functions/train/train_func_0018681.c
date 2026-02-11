ipoib_complete_recv ( struct ib_device *ibdev __unused,
				  struct ib_queue_pair *qp,
				  struct ib_address_vector *av,
				  struct io_buffer *iobuf, int rc ) {
	struct ipoib_device *ipoib = ib_qp_get_ownerdata ( qp );
	struct net_device *netdev = ipoib->netdev;
	struct ipoib_hdr *ipoib_hdr;
	struct ipoib_mac ll_src;
	struct ipoib_peer *src;


	if ( rc != 0 ) {
		netdev_rx_err ( netdev, iobuf, rc );
		return;
	}


	if ( iob_len ( iobuf ) < sizeof ( struct ipoib_hdr ) ) {
		DBGC ( ipoib, "IPoIB %p received packet too short to "
		       "contain IPoIB header\n", ipoib );
		DBGC_HD ( ipoib, iobuf->data, iob_len ( iobuf ) );
		netdev_rx_err ( netdev, iobuf, -EIO );
		return;
	}
	ipoib_hdr = iobuf->data;
	if ( ! av ) {
		DBGC ( ipoib, "IPoIB %p received packet without address "
		       "vector\n", ipoib );
		netdev_rx_err ( netdev, iobuf, -ENOTTY );
		return;
	}


	if ( av->gid_present ) {
		ll_src.flags__qpn = htonl ( av->qpn );
		memcpy ( &ll_src.gid, &av->gid, sizeof ( ll_src.gid ) );
		src = ipoib_cache_peer ( &ll_src );
		ipoib_hdr->u.peer.src = src->key;
	}


	netdev_rx ( netdev, iobuf );
}
