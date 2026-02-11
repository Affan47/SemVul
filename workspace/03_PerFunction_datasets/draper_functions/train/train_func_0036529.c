test_queue_pop ()
{
	GQueue *queue = g_queue_new ();
	gpointer data;

	g_queue_push_head (queue, "foo");
	g_queue_push_head (queue, "bar");
	g_queue_push_head (queue, "baz");

	data = g_queue_pop_head (queue);
	if (strcmp ("baz", data))
		return FAILED ("expect baz.");

	data = g_queue_pop_head (queue);
	if (strcmp ("bar", data))
		return FAILED ("expect bar.");

	data = g_queue_pop_head (queue);
	if (strcmp ("foo", data))
		return FAILED ("expect foo.");

	if (g_queue_is_empty (queue) == FALSE)
		return FAILED ("expect is_empty.");

	if (queue->length != 0)
		return FAILED ("expect 0 length .");

	g_queue_push_head (queue, "foo");
	g_queue_push_head (queue, "bar");
	g_queue_push_head (queue, "baz");

	g_queue_pop_head (queue);

	if (NULL != queue->head->prev)
		return FAILED ("HEAD: prev is wrong");
	if (strcmp ("bar", queue->head->data))
		return FAILED ("HEAD: Second element is wrong");
	if (strcmp ("foo", queue->head->next->data))
		return FAILED ("HEAD: Third element is wrong");
	if (NULL != queue->head->next->next)
		return FAILED ("HEAD: End is wrong");

	if (NULL != queue->tail->next)
		return FAILED ("TAIL: next is wrong");
	if (strcmp ("foo", queue->tail->data))
		return FAILED ("TAIL: Second element is wrong");
	if (strcmp ("bar", queue->tail->prev->data))
		return FAILED ("TAIL: First element is wrong");
	if (NULL != queue->tail->prev->prev)
		return FAILED ("TAIL: End is wrong");

	g_queue_free (queue);
	return OK;
}
