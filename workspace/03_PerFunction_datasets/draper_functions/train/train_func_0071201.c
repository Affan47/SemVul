hermon_destroy_qp ( struct ib_device *ibdev,
				struct ib_queue_pair *qp ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_queue_pair *hermon_qp = ib_qp_get_drvdata ( qp );
	int rc;


	if ( ( rc = hermon_cmd_2rst_qp ( hermon, qp->qpn ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p QPN %#lx FATAL 2RST_QP failed: %s\n",
		       hermon, qp->qpn, strerror ( rc ) );

		return;
	}


	hermon_free_mtt ( hermon, &hermon_qp->mtt );


	free_dma ( hermon_qp->wqe, hermon_qp->wqe_size );
	free_dma ( hermon_qp->recv.doorbell,
		   sizeof ( hermon_qp->recv.doorbell[0] ) );
	free ( hermon_qp );


	hermon_free_qpn ( ibdev, qp );

	ib_qp_set_drvdata ( qp, NULL );
}
