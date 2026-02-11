rndis_filter_close_device(struct rndis_device *dev)
{
	int ret;

	if (dev->state != RNDIS_DEV_DATAINITIALIZED)
		return 0;

	ret = rndis_filter_set_packet_filter(dev, 0);
	if (ret == -ENODEV)
		ret = 0;

	if (ret == 0)
		dev->state = RNDIS_DEV_INITIALIZED;

	return ret;
}
