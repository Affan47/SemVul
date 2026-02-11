show_pwm_enable(struct device *dev,
			       struct device_attribute *devattr, char *buf)
{
	int result = 0;
	struct f71882fg_data *data = f71882fg_update_device(dev);
	int nr = to_sensor_dev_attr_2(devattr)->index;

	switch ((data->pwm_enable >> 2 * nr) & 3) {
	case 0:
	case 1:
		result = 2;
		break;
	case 2:
		result = 1;
		break;
	case 3:
		if (data->type == f8000)
			result = 3;
		else
			result = 1;
		break;
	}

	return sprintf(buf, "%d\n", result);
}
