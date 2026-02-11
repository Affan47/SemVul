zforce_command(struct zforce_ts *ts, u8 cmd)
{
	struct i2c_client *client = ts->client;
	char buf[3];
	int ret;

	dev_dbg(&client->dev, "%s: 0x%x\n", __func__, cmd);

	buf[0] = FRAME_START;
	buf[1] = 1;
	buf[2] = cmd;

	mutex_lock(&ts->access_mutex);
	ret = i2c_master_send(client, &buf[0], ARRAY_SIZE(buf));
	mutex_unlock(&ts->access_mutex);
	if (ret < 0) {
		dev_err(&client->dev, "i2c send data request error: %d\n", ret);
		return ret;
	}

	return 0;
}
