iscsi_ev_context_get(struct iscsi_conn *conn, int ev_size)
{
	log_debug(2, "%s: ev_size %d\n", __FUNCTION__, ev_size);

	ipc_ev_context.data = calloc(1, ev_size);
	if (!ipc_ev_context.data)
		return NULL;

	return &ipc_ev_context;
}
