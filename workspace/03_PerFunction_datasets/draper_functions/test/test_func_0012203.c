node_send_patch_step(struct gnutella_node *n)
{
	bool ok;

	g_assert(NODE_IS_ULTRA(n));
	g_assert(NODE_IS_CONNECTED(n));
	g_assert(n->qrt_update);

	if (qrt_update_send_next(n->qrt_update))
		return;


	ok = qrt_update_was_ok(n->qrt_update);

	if (GNET_PROPERTY(node_debug) > 2)
		g_debug("QRP %spatch sending to %s done (%s)",
			(n->flags & NODE_F_STALE_QRP) ? "stale " : "",
			node_addr(n), ok ? "OK" : "FAILED");

	if (!ok) {
		qrt_unref(n->sent_query_table);
		n->sent_query_table = NULL;
	} else
		n->flags |= NODE_F_QRP_SENT;

	qrt_update_free(n->qrt_update);
	n->qrt_update = NULL;

	node_fire_node_flags_changed(n);


	if (n->flags & NODE_F_STALE_QRP) {
		struct routing_table *qrt;

		n->flags &= ~NODE_F_STALE_QRP;
	   	qrt = qrt_get_table();
		g_assert(qrt != NULL);
		node_send_qrt(n, qrt);
	}
}
