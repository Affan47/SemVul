gateway_config_stream(struct audio_device *dev, gateway_stream_cb_t cb,
				void *user_data)
{
	struct gateway *gw = dev->gateway;
	unsigned int id;

	id = connect_cb_new(gw, cb, user_data);

	if (!gw->rfcomm)
		get_records(dev);
	else if (cb)
		g_idle_add(request_stream_cb, dev);

	return id;
}
