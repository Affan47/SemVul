dev_pm_qos_expose_flags(struct device *dev, s32 val)
{
	struct dev_pm_qos_request *req;
	int ret;

	if (!device_is_registered(dev))
		return -EINVAL;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	ret = dev_pm_qos_add_request(dev, req, DEV_PM_QOS_FLAGS, val);
	if (ret < 0) {
		kfree(req);
		return ret;
	}

	pm_runtime_get_sync(dev);
	mutex_lock(&dev_pm_qos_sysfs_mtx);

	mutex_lock(&dev_pm_qos_mtx);

	if (IS_ERR_OR_NULL(dev->power.qos))
		ret = -ENODEV;
	else if (dev->power.qos->flags_req)
		ret = -EEXIST;

	if (ret < 0) {
		__dev_pm_qos_remove_request(req);
		kfree(req);
		mutex_unlock(&dev_pm_qos_mtx);
		goto out;
	}
	dev->power.qos->flags_req = req;

	mutex_unlock(&dev_pm_qos_mtx);

	ret = pm_qos_sysfs_add_flags(dev);
	if (ret)
		dev_pm_qos_drop_user_request(dev, DEV_PM_QOS_FLAGS);

 out:
	mutex_unlock(&dev_pm_qos_sysfs_mtx);
	pm_runtime_put(dev);
	return ret;
}
