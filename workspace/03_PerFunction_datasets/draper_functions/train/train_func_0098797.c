operation_emit_status_cb (StatusNode *node)
{
	StatusNode *head_node;
	gboolean emit_status;

	LOCK ();

	node->source_id = 0;


	head_node = g_queue_peek_head (&node->operation->priv->status_stack);
	emit_status = (node == head_node);

	UNLOCK ();

	if (emit_status)
		g_signal_emit (
			node->operation,
			signals[STATUS], 0,
			node->message,
			node->percent);

	return FALSE;
}
