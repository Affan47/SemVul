iscsi_flush_context_pool(struct iscsi_session *session)
{
	struct iscsi_ev_context *ev_context;
	struct iscsi_conn *conn = &session->conn[0];
	int i;

	for (i = 0; i < CONTEXT_POOL_MAX; i++) {
		ev_context = conn->context_pool[i];
		if (!ev_context)
			continue;

		if (ev_context->allocated) {
			actor_delete(&(conn->context_pool[i]->actor));
			iscsi_ev_context_put(ev_context);
		}
	}
}
