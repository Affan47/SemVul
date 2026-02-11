rtl2830_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct rtl2830_dev *dev = i2c_get_clientdata(client);
	int ret;
	u8 u8tmp;

	*status = 0;

	if (dev->sleeping)
		return 0;

	ret = rtl2830_bulk_read(client, 0x351, &u8tmp, 1);
	if (ret)
		goto err;

	u8tmp = (u8tmp >> 3) & 0x0f;
	if (u8tmp == 11) {
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	} else if (u8tmp == 10) {
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
			FE_HAS_VITERBI;
	}

	dev->fe_status = *status;

	return ret;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
