ndmconn_try_open (struct ndmconn *conn, unsigned protocol_version)
{
	int		rc;


	NDMC_WITH(ndmp0_connect_open,0)
		request->protocol_version = protocol_version;
		rc = NDMC_CALL(conn);
		if (rc) {
			ndmconn_set_err_msg (conn, "connect-open-failed");
		}
	NDMC_ENDWITH

	return rc;
}
