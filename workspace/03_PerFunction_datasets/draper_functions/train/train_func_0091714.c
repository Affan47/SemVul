show_fan_target(struct device *dev, struct device_attribute *da, char *buf)
{
	struct emc2103_data *data = emc2103_update_device(dev);
	int rpm = 0;


	if ((data->fan_target != 0) && ((data->fan_target & 0x1fe0) != 0x1fe0))
		rpm = (FAN_RPM_FACTOR * data->fan_multiplier)
			/ data->fan_target;

	return sprintf(buf, "%d\n", rpm);
}
