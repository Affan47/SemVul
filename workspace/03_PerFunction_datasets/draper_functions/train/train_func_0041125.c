finalize_config(gpointer data)
{
	struct a2dp_setup *s = data;
	GSList *l;
	struct avdtp_stream *stream = s->err ? NULL : s->stream;

	for (l = s->cb; l != NULL; ) {
		struct a2dp_setup_cb *cb = l->data;

		l = l->next;

		if (!cb->config_cb)
			continue;

		cb->config_cb(s->session, s->sep, stream, s->err,
							cb->user_data);
		setup_cb_free(cb);
	}

	return FALSE;
}
