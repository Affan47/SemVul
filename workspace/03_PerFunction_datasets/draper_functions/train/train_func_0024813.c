bt_ctf_get_top_level_scope(const struct bt_ctf_event *ctf_event,
		enum bt_ctf_scope scope)
{
	const struct bt_definition *tmp = NULL;
	const struct ctf_event_definition *event;

	if (!ctf_event)
		return NULL;

	event = ctf_event->parent;
	switch (scope) {
	case BT_TRACE_PACKET_HEADER:
		if (!event->stream)
			goto error;
		if (event->stream->trace_packet_header)
			tmp = &event->stream->trace_packet_header->p;
		break;
	case BT_STREAM_PACKET_CONTEXT:
		if (!event->stream)
			goto error;
		if (event->stream->stream_packet_context)
			tmp = &event->stream->stream_packet_context->p;
		break;
	case BT_STREAM_EVENT_HEADER:
		if (!event->stream)
			goto error;
		if (event->stream->stream_event_header)
			tmp = &event->stream->stream_event_header->p;
		break;
	case BT_STREAM_EVENT_CONTEXT:
		if (!event->stream)
			goto error;
		if (event->stream->stream_event_context)
			tmp = &event->stream->stream_event_context->p;
		break;
	case BT_EVENT_CONTEXT:
		if (event->event_context)
			tmp = &event->event_context->p;
		break;
	case BT_EVENT_FIELDS:
		if (event->event_fields)
			tmp = &event->event_fields->p;
		break;
	}
	return tmp;

error:
	return NULL;
}
