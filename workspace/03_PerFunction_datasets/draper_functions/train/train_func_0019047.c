bodystruct_free (struct _bodystruct *node)
{
	struct _bodystruct *next;

	while (node != NULL) {
		g_free (node->content.type);
		g_free (node->content.subtype);
		if (node->content.params)
			g_mime_param_destroy (node->content.params);

		g_free (node->disposition.type);
		if (node->disposition.params)
			g_mime_param_destroy (node->disposition.params);

		g_free (node->encoding);

		if (node->envelope) {
			g_free (node->envelope->date);
			g_free (node->envelope->subject);
			g_free (node->envelope->from);
			g_free (node->envelope->sender);
			g_free (node->envelope->reply_to);
			g_free (node->envelope->to);
			g_free (node->envelope->cc);
			g_free (node->envelope->bcc);
			g_free (node->envelope->in_reply_to);
			g_free (node->envelope->message_id);
			g_free (node->envelope);
		}

		if (node->subparts)
			bodystruct_free (node->subparts);

		next = node->next;
		g_free (node);
		node = next;
	}
}
