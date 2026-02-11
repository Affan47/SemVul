store_pwm(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	u8 ctl2, ctl4;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	ctl2 = lm93_read_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL2));
	ctl4 = lm93_read_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL4));
	ctl2 = (ctl2 & 0x0f) | LM93_PWM_TO_REG(val, (ctl4 & 0x07) ?
			LM93_PWM_MAP_LO_FREQ : LM93_PWM_MAP_HI_FREQ) << 4;

	data->pwm_override[nr] = LM93_PWM_FROM_REG(ctl2 >> 4,
			(ctl4 & 0x07) ?  LM93_PWM_MAP_LO_FREQ :
			LM93_PWM_MAP_HI_FREQ);
	lm93_write_byte(client, LM93_REG_PWM_CTL(nr, LM93_PWM_CTL2), ctl2);
	mutex_unlock(&data->update_lock);
	return count;
}
