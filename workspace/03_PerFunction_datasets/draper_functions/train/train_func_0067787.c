show_name(struct device *dev, struct device_attribute
			  *devattr, char *buf)
{
	int ret;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct via_cputemp_data *data = dev_get_drvdata(dev);

	if (attr->index == SHOW_NAME)
		ret = sprintf(buf, "%s\n", data->name);
	else
		ret = sprintf(buf, "Core %d\n", data->id);
	return ret;
}
