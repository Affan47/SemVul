ib_mcast_attach ( struct ib_device *ibdev, struct ib_queue_pair *qp,
		      union ib_gid *gid ) {
	struct ib_multicast_gid *mgid;
	int rc;


	mgid = zalloc ( sizeof ( *mgid ) );
	if ( ! mgid ) {
		rc = -ENOMEM;
		goto err_alloc_mgid;
	}
	memcpy ( &mgid->gid, gid, sizeof ( mgid->gid ) );
	list_add ( &mgid->list, &qp->mgids );


	if ( ( rc = ibdev->op->mcast_attach ( ibdev, qp, gid ) ) != 0 )
		goto err_dev_mcast_attach;

	return 0;

 err_dev_mcast_attach:
	list_del ( &mgid->list );
	free ( mgid );
 err_alloc_mgid:
	return rc;
}
