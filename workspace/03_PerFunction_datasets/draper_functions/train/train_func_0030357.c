max1363_smbus_send(const struct i2c_client *client, const char *buf,
		int count)
{
	int i, err;

	for (i = err = 0; err == 0 && i < count; ++i)
		err = i2c_smbus_write_byte(client, buf[i]);

	return err ? err : count;
}
