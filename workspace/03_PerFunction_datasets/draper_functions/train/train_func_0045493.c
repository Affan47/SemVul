sst_hsw_stream_set_map_config(struct sst_hsw *hsw,
	struct sst_hsw_stream *stream, u32 map,
	enum sst_hsw_channel_config config)
{
	if (stream->commited) {
		dev_err(hsw->dev, "error: stream committed for set map\n");
		return -EINVAL;
	}

	stream->request.format.map = map;
	stream->request.format.config = config;
	return 0;
}
