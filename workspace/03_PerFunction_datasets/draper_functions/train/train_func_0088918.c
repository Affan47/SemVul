lldpctl_watch_callback(lldpctl_conn_t *conn,
    lldpctl_change_callback cb,
    void *data)
{
	int rc;

	RESET_ERROR(conn);

	rc = _lldpctl_do_something(conn,
	    CONN_STATE_SET_WATCH_SEND, CONN_STATE_SET_WATCH_RECV, NULL,
	    SUBSCRIBE, NULL, NULL, NULL, NULL);
	if (rc == 0) {
		conn->watch_cb = cb;
		conn->watch_data = data;
	}
	return rc;
}
