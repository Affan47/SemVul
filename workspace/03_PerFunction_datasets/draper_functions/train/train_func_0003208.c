set_fan_min(struct device *dev, struct device_attribute
			   *devattr, const char *buf, size_t count)
{
	struct pc87427_data *data = dev_get_drvdata(dev);
	int nr = to_sensor_dev_attr(devattr)->index;
	unsigned long val;
	int iobase = data->address[LD_FAN];

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;

	mutex_lock(&data->lock);
	outb(BANK_FM(nr), iobase + PC87427_REG_BANK);


	outb(0, iobase + PC87427_REG_FAN_STATUS);
	data->fan_min[nr] = fan_to_reg(val);
	outw(data->fan_min[nr], iobase + PC87427_REG_FAN_MIN);
	outb(FAN_STATUS_MONEN, iobase + PC87427_REG_FAN_STATUS);
	mutex_unlock(&data->lock);

	return count;
}
