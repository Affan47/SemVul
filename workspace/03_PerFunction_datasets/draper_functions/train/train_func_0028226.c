show_mode(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct virtual_consumer_data *data = dev_get_drvdata(dev);

	switch (data->mode) {
	case REGULATOR_MODE_FAST:
		return sprintf(buf, "fast\n");
	case REGULATOR_MODE_NORMAL:
		return sprintf(buf, "normal\n");
	case REGULATOR_MODE_IDLE:
		return sprintf(buf, "idle\n");
	case REGULATOR_MODE_STANDBY:
		return sprintf(buf, "standby\n");
	default:
		return sprintf(buf, "unknown\n");
	}
}
