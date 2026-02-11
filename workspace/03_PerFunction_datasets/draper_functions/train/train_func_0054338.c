set_pwm(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;

	struct it87_data *data = dev_get_drvdata(dev);
	long val;

	if (kstrtol(buf, 10, &val) < 0 || val < 0 || val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	if (has_newer_autopwm(data)) {


		if (data->pwm_ctrl[nr] & 0x80) {
			mutex_unlock(&data->update_lock);
			return -EBUSY;
		}
		data->pwm_duty[nr] = pwm_to_reg(data, val);
		it87_write_value(data, IT87_REG_PWM_DUTY(nr),
				 data->pwm_duty[nr]);
	} else {
		data->pwm_duty[nr] = pwm_to_reg(data, val);


		if (!(data->pwm_ctrl[nr] & 0x80)) {
			data->pwm_ctrl[nr] = data->pwm_duty[nr];
			it87_write_value(data, IT87_REG_PWM(nr),
					 data->pwm_ctrl[nr]);
		}
	}
	mutex_unlock(&data->update_lock);
	return count;
}
