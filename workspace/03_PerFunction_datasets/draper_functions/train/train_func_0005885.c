c2port_store_flash_erase(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct c2port_device *c2dev = dev_get_drvdata(dev);
	int ret;


	if (!c2dev->access || !c2dev->flash_access)
		return -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_write_flash_erase(c2dev);
	mutex_unlock(&c2dev->mutex);

	if (ret < 0) {
		dev_err(c2dev->dev, "cannot erase %s flash\n", c2dev->name);
		return ret;
	}

	return count;
}
