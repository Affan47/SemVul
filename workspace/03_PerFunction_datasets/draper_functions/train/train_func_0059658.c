it913x_remove(struct i2c_client *client)
{
	struct it913x_dev *dev = i2c_get_clientdata(client);
	struct dvb_frontend *fe = dev->fe;

	dev_dbg(&client->dev, "\n");

	memset(&fe->ops.tuner_ops, 0, sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = NULL;
	regmap_exit(dev->regmap);
	kfree(dev);

	return 0;
}
