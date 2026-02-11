set_pwm_auto_point_pwm(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct vt1211_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int ap = sensor_attr_2->nr;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->pwm_auto_pwm[ix][ap] = clamp_val(val, 0, 255);
	vt1211_write8(data, VT1211_REG_PWM_AUTO_PWM(ix, ap),
		      data->pwm_auto_pwm[ix][ap]);
	mutex_unlock(&data->update_lock);

	return count;
}
