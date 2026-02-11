arbel_alloc_qpn ( struct ib_device *ibdev,
			     struct ib_queue_pair *qp ) {
	struct arbel *arbel = ib_get_drvdata ( ibdev );
	unsigned int port_offset;
	int qpn_offset;


	port_offset = ( ibdev->port - ARBEL_PORT_BASE );

	switch ( qp->type ) {
	case IB_QPT_SMI:
		qp->qpn = ( arbel->special_qpn_base + port_offset );
		return 0;
	case IB_QPT_GSI:
		qp->qpn = ( arbel->special_qpn_base + 2 + port_offset );
		return 0;
	case IB_QPT_UD:
	case IB_QPT_RC:

		qpn_offset = arbel_bitmask_alloc ( arbel->qp_inuse,
						   ARBEL_MAX_QPS );
		if ( qpn_offset < 0 ) {
			DBGC ( arbel, "Arbel %p out of queue pairs\n",
			       arbel );
			return qpn_offset;
		}
		qp->qpn = ( ( random() & ARBEL_QPN_RANDOM_MASK ) |
			    ( arbel->qpn_base + qpn_offset ) );
		return 0;
	default:
		DBGC ( arbel, "Arbel %p unsupported QP type %d\n",
		       arbel, qp->type );
		return -ENOTSUP;
	}
}
