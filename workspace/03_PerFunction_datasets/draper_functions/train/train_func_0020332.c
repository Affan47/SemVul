show_fan(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int nr = to_sensor_dev_attr(attr)->index;
	struct adm1031_data *data = adm1031_update_device(dev);
	int value;

	value = trust_fan_readings(data, nr) ? FAN_FROM_REG(data->fan[nr],
				 FAN_DIV_FROM_REG(data->fan_div[nr])) : 0;
	return sprintf(buf, "%d\n", value);
}
