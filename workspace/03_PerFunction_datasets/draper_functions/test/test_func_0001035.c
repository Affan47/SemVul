devm_sigmadsp_init_i2c(struct i2c_client *client,
	const struct sigmadsp_ops *ops,	const char *firmware_name)
{
	struct sigmadsp *sigmadsp;

	sigmadsp = devm_sigmadsp_init(&client->dev, ops, firmware_name);
	if (IS_ERR(sigmadsp))
		return sigmadsp;

	sigmadsp->control_data = client;
	sigmadsp->write = sigmadsp_write_i2c;
	sigmadsp->read = sigmadsp_read_i2c;

	return sigmadsp;
}
