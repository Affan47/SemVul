log_tcp_close(struct triton_context_t *ctx)
{
	struct tcp_target_t *t;

	while (!list_empty(&targets)) {
		t = list_entry(targets.next, typeof(*t), entry);
		list_del(&t->entry);
		if (t->conn_timer.tpd)
			triton_timer_del(&t->conn_timer);
		else {
			t->connected = 0;
			triton_md_unregister_handler(&t->hnd, 1);
		}
	}

	triton_context_unregister(&tcp_ctx);
}
