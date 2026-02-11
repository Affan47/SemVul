filter_check_discard(struct trace_event_file *file, void *rec,
			 struct ring_buffer *buffer,
			 struct ring_buffer_event *event)
{
	if (unlikely(file->flags & EVENT_FILE_FL_FILTERED) &&
	    !filter_match_preds(file->filter, rec)) {
		ring_buffer_discard_commit(buffer, event);
		return 1;
	}

	return 0;
}
