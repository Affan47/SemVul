sdev_store_delete(struct device *dev, struct device_attribute *attr,
		  const char *buf, size_t count)
{
	if (device_remove_file_self(dev, attr))
		scsi_remove_device(to_scsi_device(dev));
	return count;
}
