arbel_mcast_attach ( struct ib_device *ibdev,
				struct ib_queue_pair *qp,
				struct ib_gid *gid ) {
	struct arbel *arbel = ib_get_drvdata ( ibdev );
	struct arbelprm_mgm_hash hash;
	struct arbelprm_mgm_entry mgm;
	unsigned int index;
	int rc;


	if ( ( rc = arbel_cmd_mgid_hash ( arbel, gid, &hash ) ) != 0 ) {
		DBGC ( arbel, "Arbel %p could not hash GID: %s\n",
		       arbel, strerror ( rc ) );
		return rc;
	}
	index = MLX_GET ( &hash, hash );


	if ( ( rc = arbel_cmd_read_mgm ( arbel, index, &mgm ) ) != 0 ) {
		DBGC ( arbel, "Arbel %p could not read MGM %#x: %s\n",
		       arbel, index, strerror ( rc ) );
		return rc;
	}
	if ( MLX_GET ( &mgm, mgmqp_0.qi ) != 0 ) {


		DBGC ( arbel, "Arbel %p MGID index %#x already in use\n",
		       arbel, index );
		return -EBUSY;
	}


	MLX_FILL_2 ( &mgm, 8,
		     mgmqp_0.qpn_i, qp->qpn,
		     mgmqp_0.qi, 1 );
	memcpy ( &mgm.u.dwords[4], gid, sizeof ( *gid ) );
	if ( ( rc = arbel_cmd_write_mgm ( arbel, index, &mgm ) ) != 0 ) {
		DBGC ( arbel, "Arbel %p could not write MGM %#x: %s\n",
		       arbel, index, strerror ( rc ) );
		return rc;
	}

	return 0;
}
