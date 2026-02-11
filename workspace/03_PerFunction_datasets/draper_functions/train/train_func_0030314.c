kxcjk1013_set_range(struct kxcjk1013_data *data, int range_index)
{
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, KXCJK1013_REG_CTRL1);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		return ret;
	}

	ret &= ~(KXCJK1013_REG_CTRL1_BIT_GSEL0 |
		 KXCJK1013_REG_CTRL1_BIT_GSEL1);
	ret |= (KXCJK1013_scale_table[range_index].gsel_0 << 3);
	ret |= (KXCJK1013_scale_table[range_index].gsel_1 << 4);

	ret = i2c_smbus_write_byte_data(data->client,
					KXCJK1013_REG_CTRL1,
					ret);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		return ret;
	}

	data->range = range_index;

	return 0;
}
