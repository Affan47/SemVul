sst_hsw_stream_format(struct sst_hsw *hsw, struct sst_hsw_stream *stream,
	enum sst_hsw_stream_path_id path_id,
	enum sst_hsw_stream_type stream_type,
	enum sst_hsw_stream_format format_id)
{
	if (stream->commited) {
		dev_err(hsw->dev, "error: stream committed for set format\n");
		return -EINVAL;
	}

	stream->request.path_id = path_id;
	stream->request.stream_type = stream_type;
	stream->request.format_id = format_id;

	trace_hsw_stream_alloc_request(stream, &stream->request);

	return 0;
}
