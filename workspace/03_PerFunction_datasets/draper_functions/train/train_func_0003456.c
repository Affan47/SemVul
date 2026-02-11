ib_cmrc_open ( struct interface *xfer, struct ib_device *ibdev,
		   union ib_gid *dgid, union ib_guid *service_id ) {
	struct ib_cmrc_connection *cmrc;
	int rc;


	cmrc = zalloc ( sizeof ( *cmrc ) );
	if ( ! cmrc ) {
		rc = -ENOMEM;
		goto err_alloc;
	}
	ref_init ( &cmrc->refcnt, NULL );
	intf_init ( &cmrc->xfer, &ib_cmrc_xfer_desc, &cmrc->refcnt );
	cmrc->ibdev = ibdev;
	memcpy ( &cmrc->dgid, dgid, sizeof ( cmrc->dgid ) );
	memcpy ( &cmrc->service_id, service_id, sizeof ( cmrc->service_id ) );
	process_init_stopped ( &cmrc->shutdown, &ib_cmrc_shutdown_desc,
			       &cmrc->refcnt );


	if ( ( rc = ib_open ( ibdev ) ) != 0 ) {
		DBGC ( cmrc, "CMRC %p could not open device: %s\n",
		       cmrc, strerror ( rc ) );
		goto err_open;
	}


	cmrc->cq = ib_create_cq ( ibdev, IB_CMRC_NUM_CQES,
				  &ib_cmrc_completion_ops );
	if ( ! cmrc->cq ) {
		DBGC ( cmrc, "CMRC %p could not create completion queue\n",
		       cmrc );
		rc = -ENOMEM;
		goto err_create_cq;
	}


	cmrc->qp = ib_create_qp ( ibdev, IB_QPT_RC, IB_CMRC_NUM_SEND_WQES,
				  cmrc->cq, IB_CMRC_NUM_RECV_WQES, cmrc->cq );
	if ( ! cmrc->qp ) {
		DBGC ( cmrc, "CMRC %p could not create queue pair\n", cmrc );
		rc = -ENOMEM;
		goto err_create_qp;
	}
	ib_qp_set_ownerdata ( cmrc->qp, cmrc );
	DBGC ( cmrc, "CMRC %p using QPN %lx\n", cmrc, cmrc->qp->qpn );


	intf_plug_plug ( &cmrc->xfer, xfer );
	return 0;

	ib_destroy_qp ( ibdev, cmrc->qp );
 err_create_qp:
	ib_destroy_cq ( ibdev, cmrc->cq );
 err_create_cq:
	ib_close ( ibdev );
 err_open:
	ref_put ( &cmrc->refcnt );
 err_alloc:
	return rc;
}
