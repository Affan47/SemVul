ib_post_send ( struct ib_device *ibdev, struct ib_queue_pair *qp,
		   struct ib_address_vector *dest,
		   struct io_buffer *iobuf ) {
	struct ib_address_vector dest_copy;
	int rc;


	if ( qp->send.fill >= qp->send.num_wqes ) {
		DBGC ( ibdev, "IBDEV %p QPN %#lx send queue full\n",
		       ibdev, qp->qpn );
		return -ENOBUFS;
	}


	if ( ! dest )
		dest = &qp->av;


	memcpy ( &dest_copy, dest, sizeof ( dest_copy ) );
	dest = &dest_copy;


	if ( ! dest->qkey )
		dest->qkey = qp->qkey;
	if ( ! dest->rate )
		dest->rate = IB_RATE_2_5;


	if ( ( rc = ibdev->op->post_send ( ibdev, qp, dest, iobuf ) ) != 0 ) {
		DBGC ( ibdev, "IBDEV %p QPN %#lx could not post send WQE: "
		       "%s\n", ibdev, qp->qpn, strerror ( rc ) );
		return rc;
	}

	qp->send.fill++;
	return 0;
}
