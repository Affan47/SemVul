cyapa_show_product_id(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct cyapa *cyapa = dev_get_drvdata(dev);
	int size;
	int error;

	error = mutex_lock_interruptible(&cyapa->state_sync_lock);
	if (error)
		return error;
	size = scnprintf(buf, PAGE_SIZE, "%s\n", cyapa->product_id);
	mutex_unlock(&cyapa->state_sync_lock);
	return size;
}
