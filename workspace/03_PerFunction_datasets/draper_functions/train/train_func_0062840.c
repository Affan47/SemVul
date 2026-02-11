conn_reply_single(const client_conn_t *conn, const char *path, const char *status)
{
    if (conn->id) {
	if (path)
	    return mdprintf(conn->sd, "%u: %s: %s%c", conn->id, path, status, conn->term);
	return mdprintf(conn->sd, "%u: %s%c", conn->id, status, conn->term);
    }
    if (path)
	return mdprintf(conn->sd, "%s: %s%c", path, status, conn->term);
    return mdprintf(conn->sd, "%s%c", status, conn->term);
}
