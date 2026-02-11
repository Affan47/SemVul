bma180_soft_reset(struct bma180_data *data)
{
	int ret = i2c_smbus_write_byte_data(data->client,
		data->part_info->softreset_reg, BMA180_RESET_VAL);

	if (ret)
		dev_err(&data->client->dev, "failed to reset the chip\n");

	return ret;
}
