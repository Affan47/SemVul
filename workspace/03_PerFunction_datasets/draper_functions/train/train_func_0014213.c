e4000_set_lna_gain(struct dvb_frontend *fe)
{
	struct e4000_dev *dev = fe->tuner_priv;
	struct i2c_client *client = dev->client;
	int ret;
	u8 u8tmp;

	dev_dbg(&client->dev, "lna auto=%d->%d val=%d->%d\n",
		dev->lna_gain_auto->cur.val, dev->lna_gain_auto->val,
		dev->lna_gain->cur.val, dev->lna_gain->val);

	if (dev->lna_gain_auto->val && dev->if_gain_auto->cur.val)
		u8tmp = 0x17;
	else if (dev->lna_gain_auto->val)
		u8tmp = 0x19;
	else if (dev->if_gain_auto->cur.val)
		u8tmp = 0x16;
	else
		u8tmp = 0x10;

	ret = regmap_write(dev->regmap, 0x1a, u8tmp);
	if (ret)
		goto err;

	if (dev->lna_gain_auto->val == false) {
		ret = regmap_write(dev->regmap, 0x14, dev->lna_gain->val);
		if (ret)
			goto err;
	}

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
