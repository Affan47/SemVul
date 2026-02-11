bh1770_lux_result_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	ssize_t ret;
	long timeout;

	if (pm_runtime_suspended(dev))
		return -EIO;

	timeout = wait_event_interruptible_timeout(chip->wait,
					!chip->lux_wait_result,
					msecs_to_jiffies(BH1770_TIMEOUT));
	if (!timeout)
		return -EIO;

	mutex_lock(&chip->mutex);
	ret = sprintf(buf, "%d\n", bh1770_lux_read_result(chip));
	mutex_unlock(&chip->mutex);

	return ret;
}
