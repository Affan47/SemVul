rtl2830_pid_filter_ctrl(struct dvb_frontend *fe, int onoff)
{
	struct i2c_client *client = fe->demodulator_priv;
	int ret;
	u8 u8tmp;

	dev_dbg(&client->dev, "onoff=%d\n", onoff);


	if (onoff)
		u8tmp = 0x80;
	else
		u8tmp = 0x00;

	ret = rtl2830_update_bits(client, 0x061, 0x80, u8tmp);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
