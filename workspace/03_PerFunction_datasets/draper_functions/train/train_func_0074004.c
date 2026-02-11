iscsi_ev_context_free(iscsi_conn_t *conn)
{
	int i;

	for (i = 0; i < CONTEXT_POOL_MAX; i++) {
		if (!conn->context_pool[i])
			continue;

		if (conn->context_pool[i]->allocated)

			log_error("BUG: context_pool leak %p",
				  conn->context_pool[i]);
		free(conn->context_pool[i]);
	}
}
