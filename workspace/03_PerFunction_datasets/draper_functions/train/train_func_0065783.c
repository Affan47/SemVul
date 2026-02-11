set_pwm_temp_map(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;

	struct it87_data *data = dev_get_drvdata(dev);
	long val;
	u8 reg;


	if (!has_old_autopwm(data)) {
		dev_notice(dev, "Mapping change disabled for safety reasons\n");
		return -EINVAL;
	}

	if (kstrtol(buf, 10, &val) < 0)
		return -EINVAL;

	switch (val) {
	case (1 << 0):
		reg = 0x00;
		break;
	case (1 << 1):
		reg = 0x01;
		break;
	case (1 << 2):
		reg = 0x02;
		break;
	default:
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);
	data->pwm_temp_map[nr] = reg;


	if (data->pwm_ctrl[nr] & 0x80) {
		data->pwm_ctrl[nr] = 0x80 | data->pwm_temp_map[nr];
		it87_write_value(data, IT87_REG_PWM(nr), data->pwm_ctrl[nr]);
	}
	mutex_unlock(&data->update_lock);
	return count;
}
