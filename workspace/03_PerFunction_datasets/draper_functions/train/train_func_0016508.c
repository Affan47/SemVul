ipoib_transmit ( struct net_device *netdev,
			    struct io_buffer *iobuf ) {
	struct ipoib_device *ipoib = netdev->priv;
	struct ib_device *ibdev = ipoib->ibdev;
	struct ipoib_hdr *ipoib_hdr;
	struct ipoib_peer *dest;
	struct ib_address_vector av;
	int rc;


	if ( iob_len ( iobuf ) < sizeof ( *ipoib_hdr ) ) {
		DBGC ( ipoib, "IPoIB %p buffer too short\n", ipoib );
		return -EINVAL;
	}
	ipoib_hdr = iobuf->data;


	if ( ! ib_link_ok ( ibdev ) )
		return -ENETUNREACH;


	dest = ipoib_lookup_peer_by_key ( ipoib_hdr->u.peer.dest );
	if ( ! dest )
		return -ENXIO;
	ipoib_hdr->u.reserved = 0;


	memset ( &av, 0, sizeof ( av ) );
	av.qpn = ( ntohl ( dest->mac.flags__qpn ) & IB_QPN_MASK );
	av.gid_present = 1;
	memcpy ( &av.gid, &dest->mac.gid, sizeof ( av.gid ) );
	if ( ( rc = ib_resolve_path ( ibdev, &av ) ) != 0 ) {

		return rc;
	}

	return ib_post_send ( ibdev, ipoib->qp, &av, iobuf );
}
