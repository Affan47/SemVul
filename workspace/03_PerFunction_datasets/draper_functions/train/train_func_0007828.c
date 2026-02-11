server_monitor_latency_show(struct device *dev,
					   struct device_attribute *dev_attr,
					   char *buf)
{
	struct hv_device *hv_dev = device_to_hv_device(dev);

	if (!hv_dev->channel)
		return -ENODEV;
	return sprintf(buf, "%d\n",
		       channel_latency(hv_dev->channel,
				       vmbus_connection.monitor_pages[0]));
}
