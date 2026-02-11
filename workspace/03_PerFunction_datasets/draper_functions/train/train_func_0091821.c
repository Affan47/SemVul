show_pwm_enable(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int nr = (to_sensor_dev_attr(attr))->index;
	struct lm93_data *data = lm93_update_device(dev);
	u8 ctl2;
	long rc;

	ctl2 = data->block9[nr][LM93_PWM_CTL2];
	if (ctl2 & 0x01)
		rc = ((ctl2 & 0xF0) == 0xF0) ? 0 : 1;
	else
		rc = 2;
	return sprintf(buf, "%ld\n", rc);
}
