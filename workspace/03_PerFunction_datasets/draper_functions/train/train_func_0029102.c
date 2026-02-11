show_fan(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	struct vt8231_data *data = vt8231_update_device(dev);
	return sprintf(buf, "%d\n", FAN_FROM_REG(data->fan[nr],
				DIV_FROM_REG(data->fan_div[nr])));
}
