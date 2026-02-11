adc128_show_in(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct adc128_data *data = adc128_update_device(dev);
	int index = to_sensor_dev_attr_2(attr)->index;
	int nr = to_sensor_dev_attr_2(attr)->nr;
	int val;

	if (IS_ERR(data))
		return PTR_ERR(data);

	val = DIV_ROUND_CLOSEST(data->in[index][nr] * data->vref, 4095);
	return sprintf(buf, "%d\n", val);
}
