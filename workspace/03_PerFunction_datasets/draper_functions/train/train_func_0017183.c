mei_cl_device_remove(struct device *dev)
{
	struct mei_cl_device *cldev = to_mei_cl_device(dev);
	struct mei_cl_driver *cldrv;
	int ret = 0;

	if (!cldev || !dev->driver)
		return 0;

	if (cldev->event_cb) {
		cldev->event_cb = NULL;
		cancel_work_sync(&cldev->event_work);
	}

	cldrv = to_mei_cl_driver(dev->driver);
	if (cldrv->remove)
		ret = cldrv->remove(cldev);

	module_put(THIS_MODULE);
	dev->driver = NULL;
	return ret;

}
