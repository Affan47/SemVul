set_pwm(struct device *dev, struct device_attribute *devattr,
		       const char *buf, size_t count)
{
	struct f71805f_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int nr = attr->index;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	if (val > 255)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	data->pwm[nr] = val;
	f71805f_write8(data, F71805F_REG_PWM_DUTY(nr), data->pwm[nr]);
	mutex_unlock(&data->update_lock);

	return count;
}
