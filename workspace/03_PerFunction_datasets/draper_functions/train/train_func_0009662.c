show_temp(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct w83l786ng_data *data = w83l786ng_update_device(dev);
	return sprintf(buf, "%d\n", TEMP_FROM_REG(data->temp[nr][index]));
}
