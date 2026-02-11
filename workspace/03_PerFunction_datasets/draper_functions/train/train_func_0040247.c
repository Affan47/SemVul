sst_unregister_dsp(struct sst_device *dev)
{
	if (WARN_ON(!dev))
		return -EINVAL;
	if (dev != sst)
		return -EINVAL;

	mutex_lock(&sst_lock);

	if (!sst) {
		mutex_unlock(&sst_lock);
		return -EIO;
	}

	module_put(sst->dev->driver->owner);
	dev_dbg(dev->dev, "unreg %s\n", sst->name);
	sst = NULL;
	mutex_unlock(&sst_lock);
	return 0;
}
