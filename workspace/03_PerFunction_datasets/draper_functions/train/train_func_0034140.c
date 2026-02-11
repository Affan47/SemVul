bh1770_prox_result_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	ssize_t ret;

	mutex_lock(&chip->mutex);
	if (chip->prox_enable_count && !pm_runtime_suspended(dev))
		ret = sprintf(buf, "%d\n", chip->prox_data);
	else
		ret = -EIO;
	mutex_unlock(&chip->mutex);
	return ret;
}
