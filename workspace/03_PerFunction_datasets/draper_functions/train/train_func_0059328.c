show_pwm(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	struct w83793_data *data = w83793_update_device(dev);
	u16 val;
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;

	if (nr == PWM_STOP_TIME)
		val = TIME_FROM_REG(data->pwm_stop_time[index]);
	else
		val = (data->pwm[index][nr] & 0x3f) << 2;

	return sprintf(buf, "%d\n", val);
}
