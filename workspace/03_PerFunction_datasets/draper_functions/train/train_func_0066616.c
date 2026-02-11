source_request_server_auth_request_cancel_all (ESourceRegistryServer *server)
{
	GHashTableIter iter;
	gpointer value;

	g_mutex_lock (&server->priv->auth_lock);

	g_hash_table_iter_init (&iter, server->priv->waiting_auths);

	while (g_hash_table_iter_next (&iter, NULL, &value)) {
		GQueue *queue = value;
		GList *list, *link;

		list = g_queue_peek_head_link (queue);

		for (link = list; link != NULL; link = g_list_next (link)) {
			AuthRequest *request = link->data;
			g_cancellable_cancel (request->cancellable);
		}
	}

	g_hash_table_iter_init (&iter, server->priv->running_auths);

	while (g_hash_table_iter_next (&iter, NULL, &value)) {
		AuthRequest *request = value;
		g_cancellable_cancel (request->cancellable);
	}

	g_mutex_unlock (&server->priv->auth_lock);
}
