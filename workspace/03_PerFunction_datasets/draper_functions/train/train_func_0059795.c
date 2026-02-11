hermon_mcast_attach ( struct ib_device *ibdev,
				 struct ib_queue_pair *qp,
				 struct ib_gid *gid ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermonprm_mgm_hash hash;
	struct hermonprm_mcg_entry mcg;
	unsigned int index;
	int rc;


	if ( ( rc = hermon_cmd_mgid_hash ( hermon, gid, &hash ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p could not hash GID: %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}
	index = MLX_GET ( &hash, hash );


	if ( ( rc = hermon_cmd_read_mcg ( hermon, index, &mcg ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p could not read MCG %#x: %s\n",
		       hermon, index, strerror ( rc ) );
		return rc;
	}
	if ( MLX_GET ( &mcg, hdr.members_count ) != 0 ) {


		DBGC ( hermon, "Hermon %p MGID index %#x already in use\n",
		       hermon, index );
		return -EBUSY;
	}


	MLX_FILL_1 ( &mcg, 1, hdr.members_count, 1 );
	MLX_FILL_1 ( &mcg, 8, qp[0].qpn, qp->qpn );
	memcpy ( &mcg.u.dwords[4], gid, sizeof ( *gid ) );
	if ( ( rc = hermon_cmd_write_mcg ( hermon, index, &mcg ) ) != 0 ) {
		DBGC ( hermon, "Hermon %p could not write MCG %#x: %s\n",
		       hermon, index, strerror ( rc ) );
		return rc;
	}

	return 0;
}
