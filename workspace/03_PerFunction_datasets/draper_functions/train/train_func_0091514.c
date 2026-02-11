baytrail_i2c_release(struct dw_i2c_dev *dev)
{
	if (!dev || !dev->dev)
		return;

	if (!dev->acquire_lock)
		return;

	reset_semaphore(dev->dev);
	dev_dbg(dev->dev, "punit semaphore held for %ums\n",
		jiffies_to_msecs(jiffies - acquired));
}
