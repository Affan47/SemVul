_lldpctl_needs(lldpctl_conn_t *conn, size_t length)
{
	uint8_t *buffer = NULL;
	ssize_t  rc;

	if ((buffer = malloc(length)) == NULL)
		return SET_ERROR(conn, LLDPCTL_ERR_NOMEM);
	rc = conn->recv(conn, buffer, length, conn->user_data);
	if (rc < 0) {
		free(buffer);
		return SET_ERROR(conn, rc);
	}
	if (rc == 0) {
		free(buffer);
		return SET_ERROR(conn, LLDPCTL_ERR_EOF);
	}
	rc = lldpctl_recv(conn, buffer, rc);
	free(buffer);
	if (rc < 0)
		return SET_ERROR(conn, rc);
	RESET_ERROR(conn);
	return rc;
}
