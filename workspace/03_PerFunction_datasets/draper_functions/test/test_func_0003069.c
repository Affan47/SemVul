ndmp_sxa_data_start_backup (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn)
{
	int			rc;
	ndmp9_error		error;

      NDMS_WITH(ndmp9_data_start_backup)
	rc = data_ok_bu_type (sess, xa, ref_conn, request->bu_type);
	if (rc) {
		return rc;
	}

	if (request->addr.addr_type != NDMP9_ADDR_AS_CONNECTED) {
		rc = data_can_connect_and_start (sess, xa, ref_conn,
				&request->addr, NDMP9_MOVER_MODE_READ);
	} else {
		rc = data_can_start (sess, xa, ref_conn,
				NDMP9_MOVER_MODE_READ);
	}
	if (rc) {
		return rc;
	}

	strcpy (sess->data_acb.bu_type, request->bu_type);

	error = data_copy_environment (sess,
			request->env.env_val, request->env.env_len);
	if (error != NDMP9_NO_ERR) {
		ndmda_belay (sess);
		NDMADR_RAISE(error, "copy-env");
	}

	if (request->addr.addr_type != NDMP9_ADDR_AS_CONNECTED) {
		rc = data_connect (sess, xa, ref_conn, &request->addr);
		if (rc) {
			ndmda_belay (sess);
			return rc;
		}
	}

	error = ndmda_data_start_backup (sess);
	if (error != NDMP9_NO_ERR) {

		ndmda_belay (sess);
		NDMADR_RAISE(error, "start_backup");
	}

	return 0;
      NDMS_ENDWITH
}
