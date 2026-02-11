store_pwm_auto_point_temp(struct device *dev,
					 struct device_attribute *devattr,
					 const char *buf, size_t count)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	int err, pwm = to_sensor_dev_attr_2(devattr)->index;
	int point = to_sensor_dev_attr_2(devattr)->nr;
	long val;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	val /= 1000;

	if (data->auto_point_temp_signed)
		val = clamp_val(val, -128, 127);
	else
		val = clamp_val(val, 0, 127);

	mutex_lock(&data->update_lock);
	f71882fg_write8(data, F71882FG_REG_POINT_TEMP(pwm, point), val);
	data->pwm_auto_point_temp[pwm][point] = val;
	mutex_unlock(&data->update_lock);

	return count;
}
