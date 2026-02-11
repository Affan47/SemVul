ndma_call (struct ndmconn *conn, struct ndmp_xa_buf *xa)
{
	int		rc;

	rc = ndma_call_no_tattle (conn, xa);

	if (rc) {
		ndma_tattle (conn, xa, rc);
	}
	return rc;
}
