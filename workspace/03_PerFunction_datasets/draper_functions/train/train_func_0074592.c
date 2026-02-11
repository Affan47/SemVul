ib_cm_send_rtu ( struct ib_device *ibdev,
			    struct ib_mad_interface *mi,
			    struct ib_connection *conn,
			    struct ib_address_vector *av ) {
	union ib_mad mad;
	struct ib_cm_ready_to_use *ready =
		&mad.cm.cm_data.ready_to_use;
	int rc;


	memset ( &mad, 0, sizeof ( mad ) );
	mad.hdr.mgmt_class = IB_MGMT_CLASS_CM;
	mad.hdr.class_version = IB_CM_CLASS_VERSION;
	mad.hdr.method = IB_MGMT_METHOD_SEND;
	mad.hdr.attr_id = htons ( IB_CM_ATTR_READY_TO_USE );
	ready->local_id = htonl ( conn->local_id );
	ready->remote_id = htonl ( conn->remote_id );
	if ( ( rc = ib_mi_send ( ibdev, mi, &mad, av ) ) != 0 ){
		DBGC ( conn, "CM %p could not send RTU: %s\n",
		       conn, strerror ( rc ) );
		return rc;
	}

	return 0;
}
