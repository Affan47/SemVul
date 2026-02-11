bt_iter_add_trace(struct bt_iter *iter,
		struct bt_trace_descriptor *td_read)
{
	struct ctf_trace *tin;
	int stream_id, ret = 0;

	tin = container_of(td_read, struct ctf_trace, parent);


	for (stream_id = 0; stream_id < tin->streams->len;
			stream_id++) {
		struct ctf_stream_declaration *stream;
		int filenr;

		stream = g_ptr_array_index(tin->streams, stream_id);
		if (!stream)
			continue;
		for (filenr = 0; filenr < stream->streams->len;
				filenr++) {
			struct ctf_file_stream *file_stream;
			struct bt_iter_pos pos;

			file_stream = g_ptr_array_index(stream->streams,
					filenr);
			if (!file_stream)
				continue;

			pos.type = BT_SEEK_BEGIN;
			ret = babeltrace_filestream_seek(file_stream,
					&pos, stream_id);

			if (ret == EOF) {
				ret = 0;
				continue;
			} else if (ret != 0 && ret != EAGAIN) {
				goto error;
			}

			ret = bt_heap_insert(iter->stream_heap, file_stream);
			if (ret)
				goto error;
		}
	}

error:
	return ret;
}
