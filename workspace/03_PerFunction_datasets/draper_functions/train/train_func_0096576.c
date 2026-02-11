tpa6130a2_i2c_write(int reg, u8 value)
{
	struct tpa6130a2_data *data;
	int val = 0;

	if (WARN_ON(!tpa6130a2_client))
		return -EINVAL;
	data = i2c_get_clientdata(tpa6130a2_client);

	if (data->power_state) {
		val = i2c_smbus_write_byte_data(tpa6130a2_client, reg, value);
		if (val < 0) {
			dev_err(&tpa6130a2_client->dev, "Write failed\n");
			return val;
		}
	}


	data->regs[reg] = value;

	return val;
}
