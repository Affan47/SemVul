avdtp_stream_has_capability(struct avdtp_stream *stream,
				struct avdtp_service_capability *cap)
{
	GSList *l;
	struct avdtp_service_capability *stream_cap;

	for (l = stream->caps; l; l = g_slist_next(l)) {
		stream_cap = l->data;

		if (stream_cap->category != cap->category ||
			stream_cap->length != cap->length)
			continue;

		if (memcmp(stream_cap->data, cap->data, cap->length) == 0)
			return TRUE;
	}

	return FALSE;
}
