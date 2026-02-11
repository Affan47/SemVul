mag3110_request(struct mag3110_data *data)
{
	int ret, tries = 150;


	ret = i2c_smbus_write_byte_data(data->client, MAG3110_CTRL_REG1,
		data->ctrl_reg1 | MAG3110_CTRL_TM);
	if (ret < 0)
		return ret;

	while (tries-- > 0) {
		ret = i2c_smbus_read_byte_data(data->client, MAG3110_STATUS);
		if (ret < 0)
			return ret;

		if ((ret & MAG3110_STATUS_DRDY) == MAG3110_STATUS_DRDY)
			break;
		msleep(20);
	}

	if (tries < 0) {
		dev_err(&data->client->dev, "data not ready\n");
		return -EIO;
	}

	return 0;
}
