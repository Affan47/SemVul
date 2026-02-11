soup_message_queue_append (SoupMessageQueue *queue, SoupMessage *msg,
			   SoupSessionCallback callback, gpointer user_data)
{
	SoupMessageQueueItem *item;

	item = g_slice_new0 (SoupMessageQueueItem);
	item->session = g_object_ref (queue->session);
	item->async_context = soup_session_get_async_context (item->session);
	if (item->async_context)
		g_main_context_ref (item->async_context);
	item->queue = queue;
	item->msg = g_object_ref (msg);
	item->callback = callback;
	item->callback_data = user_data;
	item->cancellable = g_cancellable_new ();
	item->priority = soup_message_get_priority (msg);

	g_signal_connect (msg, "restarted",
			  G_CALLBACK (queue_message_restarted), item);


	item->ref_count = 1;

	g_mutex_lock (&queue->mutex);
	if (queue->head) {
		SoupMessageQueueItem *it = queue->head;

		while (it && it->priority >= item->priority)
			it = it->next;

		if (!it) {
			if (queue->tail) {
				queue->tail->next = item;
				item->prev = queue->tail;
			} else
				queue->head = item;
			queue->tail = item;
		} else {
			if (it != queue->head)
				it->prev->next = item;
			else
				queue->head = item;
			item->prev = it->prev;
			it->prev = item;
			item->next = it;
		}
	} else
		queue->head = queue->tail = item;

	g_mutex_unlock (&queue->mutex);
	return item;
}
