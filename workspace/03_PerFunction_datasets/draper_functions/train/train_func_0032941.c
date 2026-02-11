hym8563_rtc_alarm_irq_enable(struct device *dev,
					unsigned int enabled)
{
	struct i2c_client *client = to_i2c_client(dev);
	int data;

	data = i2c_smbus_read_byte_data(client, HYM8563_CTL2);
	if (data < 0)
		return data;

	if (enabled)
		data |= HYM8563_CTL2_AIE;
	else
		data &= ~HYM8563_CTL2_AIE;

	return i2c_smbus_write_byte_data(client, HYM8563_CTL2, data);
}
