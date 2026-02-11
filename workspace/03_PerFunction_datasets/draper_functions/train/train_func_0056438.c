show_temp_max_hyst(struct device *dev, struct device_attribute *devattr,
		   char *buf)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = w83627hf_update_device(dev);

	u16 tmp = data->temp_max_hyst[nr];
	return sprintf(buf, "%ld\n", (nr) ? (long) LM75_TEMP_FROM_REG(tmp)
					  : (long) TEMP_FROM_REG(tmp));
}
