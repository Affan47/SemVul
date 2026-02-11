data_connect (struct ndm_session *sess,
  struct ndmp_xa_buf *xa, struct ndmconn *ref_conn,
  ndmp9_addr *data_addr)
{
	struct ndm_data_agent *	da = &sess->data_acb;
	int			rc;
	ndmp9_error		error;
	char			reason[100];

	rc = data_can_connect (sess, xa, ref_conn, data_addr);
	if (rc)
		return rc;


	error = ndmis_data_connect (sess, data_addr, reason);
	if (error != NDMP9_NO_ERR) NDMADR_RAISE(error, reason);

	da->data_state.data_connection_addr = *data_addr;


	error = ndmda_data_connect (sess);
	if (error != NDMP9_NO_ERR) {

		NDMADR_RAISE(error, "!data_connect");
	}

	da->data_state.data_connection_addr = *data_addr;

	return 0;
}
