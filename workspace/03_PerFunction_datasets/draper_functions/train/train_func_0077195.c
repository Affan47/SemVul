mei_cldev_enable(struct mei_cl_device *cldev)
{
	struct mei_device *bus = cldev->bus;
	struct mei_cl *cl;
	int ret;

	cl = cldev->cl;

	if (!cl) {
		mutex_lock(&bus->device_lock);
		cl = mei_cl_alloc_linked(bus, MEI_HOST_CLIENT_ID_ANY);
		mutex_unlock(&bus->device_lock);
		if (IS_ERR(cl))
			return PTR_ERR(cl);

		cldev->cl = cl;
		cl->cldev = cldev;
	}

	mutex_lock(&bus->device_lock);
	if (mei_cl_is_connected(cl)) {
		ret = 0;
		goto out;
	}

	if (!mei_me_cl_is_active(cldev->me_cl)) {
		dev_err(&cldev->dev, "me client is not active\n");
		ret = -ENOTTY;
		goto out;
	}

	ret = mei_cl_connect(cl, cldev->me_cl, NULL);
	if (ret < 0)
		dev_err(&cldev->dev, "cannot connect\n");

out:
	mutex_unlock(&bus->device_lock);

	return ret;
}
