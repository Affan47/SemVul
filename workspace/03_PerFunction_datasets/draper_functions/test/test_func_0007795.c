blinkm_read(struct i2c_client *client, int cmd, u8 *arg)
{
	int result;
	int i;
	int retlen = blinkm_cmds[cmd].nr_ret;
	for (i = 0; i < retlen; i++) {

		result = i2c_smbus_read_byte(client);
		if (result < 0)
			return result;
		arg[i] = result;
	}

	return 0;
}
