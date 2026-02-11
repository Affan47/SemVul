nd_device_unregister(struct device *dev, enum nd_async_mode mode)
{
	switch (mode) {
	case ND_ASYNC:
		get_device(dev);
		async_schedule_domain(nd_async_device_unregister, dev,
				&nd_async_domain);
		break;
	case ND_SYNC:
		nd_synchronize();
		device_unregister(dev);
		break;
	}
}
