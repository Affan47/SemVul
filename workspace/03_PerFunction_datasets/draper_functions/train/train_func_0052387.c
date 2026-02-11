find_stream_by_rseid(struct avdtp *session,
							uint8_t rseid)
{
	GSList *l;

	for (l = session->streams; l != NULL; l = g_slist_next(l)) {
		struct avdtp_stream *stream = l->data;

		if (stream->rseid == rseid)
			return stream;
	}

	return NULL;
}
