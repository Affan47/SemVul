store_pwm_auto_spinup_time(struct device *dev,
						struct device_attribute *attr,
						const char *buf, size_t count)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 ctl3;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	ctl3 = lm93_read_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL3));
	ctl3 = (ctl3 & 0x1f) | (LM93_SPINUP_TIME_TO_REG(val) << 5 & 0xe0);
	data->block9[nr][LM93_PWM_CTL3] = ctl3;
	lm93_write_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL3), ctl3);
	mutex_unlock(&data->update_lock);
	return count;
}
