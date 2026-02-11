show_pwm_freq(struct device *dev, struct device_attribute *devattr, char *buf)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = w83627hf_update_device(dev);
	if (data->type == w83627hf)
		return sprintf(buf, "%ld\n",
			pwm_freq_from_reg_627hf(data->pwm_freq[nr]));
	else
		return sprintf(buf, "%ld\n",
			pwm_freq_from_reg(data->pwm_freq[nr]));
}
