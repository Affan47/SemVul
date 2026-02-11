da9052_read_misc_channel(struct device *dev,
					struct device_attribute *devattr,
					char *buf)
{
	struct da9052_hwmon *hwmon = dev_get_drvdata(dev);
	int channel = to_sensor_dev_attr(devattr)->index;
	int ret;

	ret = da9052_adc_manual_read(hwmon->da9052, channel);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", input_reg_to_mv(ret));
}
