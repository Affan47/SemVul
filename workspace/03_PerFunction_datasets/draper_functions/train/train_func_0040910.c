ov2659_set_streaming(struct ov2659 *ov2659, int on)
{
	struct i2c_client *client = ov2659->client;
	int ret;

	on = !!on;

	dev_dbg(&client->dev, "%s: on: %d\n", __func__, on);

	ret = ov2659_write(client, REG_SOFTWARE_STANDBY, on);
	if (ret)
		dev_err(&client->dev, "ov2659 soft standby failed\n");
}
