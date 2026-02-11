ctf_write_event(struct bt_stream_pos *pos, struct ctf_stream_definition *stream)
{
	struct ctf_stream_declaration *stream_class = stream->stream_class;
	struct ctf_event_definition *event;
	uint64_t id;
	int ret;

	id = stream->event_id;


	if (likely(stream->stream_event_header)) {
		ret = generic_rw(pos, &stream->stream_event_header->p);
		if (ret)
			goto error;
	}


	if (stream->stream_event_context) {
		ret = generic_rw(pos, &stream->stream_event_context->p);
		if (ret)
			goto error;
	}

	if (unlikely(id >= stream_class->events_by_id->len)) {
		fprintf(stderr, "[error] Event id %" PRIu64 " is outside range.\n", id);
		return -EINVAL;
	}
	event = g_ptr_array_index(stream->events_by_id, id);
	if (unlikely(!event)) {
		fprintf(stderr, "[error] Event id %" PRIu64 " is unknown.\n", id);
		return -EINVAL;
	}


	if (event->event_context) {
		ret = generic_rw(pos, &event->event_context->p);
		if (ret)
			goto error;
	}


	if (likely(event->event_fields)) {
		ret = generic_rw(pos, &event->event_fields->p);
		if (ret)
			goto error;
	}

	return 0;

error:
	fprintf(stderr, "[error] Unexpected end of stream. Either the trace data stream is corrupted or metadata description does not match data layout.\n");
	return ret;
}
