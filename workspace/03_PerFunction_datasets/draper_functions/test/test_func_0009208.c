bt_ctf_writer_create_stream(struct bt_ctf_writer *writer,
		struct bt_ctf_stream_class *stream_class)
{
	int ret;
	int stream_class_found = 0;
	size_t i;
	int stream_fd;
	struct bt_ctf_stream *stream = NULL;

	if (!writer || !stream_class) {
		goto error;
	}

	stream = bt_ctf_stream_create(stream_class);
	if (!stream) {
		goto error;
	}

	stream_fd = create_stream_file(writer, stream);
	if (stream_fd < 0 || bt_ctf_stream_set_fd(stream, stream_fd)) {
		goto error;
	}

	bt_ctf_stream_set_flush_callback(stream, (flush_func)stream_flush_cb,
		writer);
	ret = bt_ctf_stream_class_set_byte_order(stream->stream_class,
		writer->byte_order == LITTLE_ENDIAN ?
		BT_CTF_BYTE_ORDER_LITTLE_ENDIAN : BT_CTF_BYTE_ORDER_BIG_ENDIAN);
	if (ret) {
		goto error;
	}

	for (i = 0; i < writer->stream_classes->len; i++) {
		if (writer->stream_classes->pdata[i] == stream->stream_class) {
			stream_class_found = 1;
		}
	}

	if (!stream_class_found) {
		if (bt_ctf_stream_class_set_id(stream->stream_class,
			writer->next_stream_id++)) {
			goto error;
		}

		bt_ctf_stream_class_get(stream->stream_class);
		g_ptr_array_add(writer->stream_classes, stream->stream_class);
	}

	bt_ctf_stream_get(stream);
	g_ptr_array_add(writer->streams, stream);
	writer->frozen = 1;
	return stream;
error:
	bt_ctf_stream_put(stream);
	return NULL;
}
