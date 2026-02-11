gateway_get_sco_fd(struct audio_device *dev)
{
	struct gateway *gw = dev->gateway;

	if (!gw || !gw->sco)
		return -1;

	return g_io_channel_unix_get_fd(gw->sco);
}
