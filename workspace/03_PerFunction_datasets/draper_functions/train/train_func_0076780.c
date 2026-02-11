elants_i2c_send(struct i2c_client *client,
			   const void *data, size_t size)
{
	int ret;

	ret = i2c_master_send(client, data, size);
	if (ret == size)
		return 0;

	if (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "%s failed (%*ph): %d\n",
		__func__, (int)size, data, ret);

	return ret;
}
