ib_create_madx ( struct ib_device *ibdev, struct ib_mad_interface *mi,
		 union ib_mad *mad, struct ib_address_vector *av,
		 struct ib_mad_transaction_operations *op ) {
	struct ib_mad_transaction *madx;


	madx = zalloc ( sizeof ( *madx ) );
	if ( ! madx )
		return NULL;
	madx->mi = mi;
	madx->timer.expired = ib_mi_timer_expired;
	madx->op = op;


	if ( av ) {
		memcpy ( &madx->av, av, sizeof ( madx->av ) );
	} else {
		madx->av.lid = ibdev->sm_lid;
		madx->av.sl = ibdev->sm_sl;
		madx->av.qpn = IB_QPN_GSI;
		madx->av.qkey = IB_QKEY_GSI;
	}


	memcpy ( &madx->mad, mad, sizeof ( madx->mad ) );


	list_add ( &madx->list, &mi->madx );
	start_timer_nodelay ( &madx->timer );

	return madx;
}
