cm_tdbus_timeout_cleanup(void *data)
{
	struct tdbus_connection *conn;
	conn = data;
	while (conn->timers != NULL) {
		cm_tdbus_timeout_remove(conn->timers->timeout, data);
	}
}
