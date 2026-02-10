stk8312_otp_init(struct stk8312_data *data)
{
	int ret;
	int count = 10;
	struct i2c_client *client = data->client;

	ret = i2c_smbus_write_byte_data(client, STK8312_REG_OTPADDR, 0x70);
	if (ret < 0)
		goto exit_err;
	ret = i2c_smbus_write_byte_data(client, STK8312_REG_OTPCTRL, 0x02);
	if (ret < 0)
		goto exit_err;

	do {
		usleep_range(1000, 5000);
		ret = i2c_smbus_read_byte_data(client, STK8312_REG_OTPCTRL);
		if (ret < 0)
			goto exit_err;
		count--;
	} while (!(ret & BIT(7)) && count > 0);

	if (count == 0) {
		ret = -ETIMEDOUT;
		goto exit_err;
	}

	ret = i2c_smbus_read_byte_data(client, STK8312_REG_OTPDATA);
	if (ret == 0)
		ret = -EINVAL;
	if (ret < 0)
		goto exit_err;

	ret = i2c_smbus_write_byte_data(data->client, STK8312_REG_AFECTRL, ret);
	if (ret < 0)
		goto exit_err;
	msleep(150);

	return 0;

exit_err:
	dev_err(&client->dev, "failed to initialize sensor\n");
	return ret;
}
