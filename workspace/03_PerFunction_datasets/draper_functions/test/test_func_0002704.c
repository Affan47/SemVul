it913x_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct it913x_config *cfg = client->dev.platform_data;
	struct dvb_frontend *fe = cfg->fe;
	struct it913x_dev *dev;
	int ret;
	char *chip_ver_str;
	static const struct regmap_config regmap_config = {
		.reg_bits = 24,
		.val_bits = 8,
	};

	dev = kzalloc(sizeof(struct it913x_dev), GFP_KERNEL);
	if (dev == NULL) {
		ret = -ENOMEM;
		dev_err(&client->dev, "kzalloc() failed\n");
		goto err;
	}

	dev->client = client;
	dev->fe = cfg->fe;
	dev->chip_ver = cfg->chip_ver;
	dev->role = cfg->role;
	dev->regmap = regmap_init_i2c(client, &regmap_config);
	if (IS_ERR(dev->regmap)) {
		ret = PTR_ERR(dev->regmap);
		goto err_kfree;
	}

	fe->tuner_priv = dev;
	memcpy(&fe->ops.tuner_ops, &it913x_tuner_ops,
			sizeof(struct dvb_tuner_ops));
	i2c_set_clientdata(client, dev);

	if (dev->chip_ver == 1)
		chip_ver_str = "AX";
	else if (dev->chip_ver == 2)
		chip_ver_str = "BX";
	else
		chip_ver_str = "??";

	dev_info(&dev->client->dev, "ITE IT913X %s successfully attached\n",
			chip_ver_str);
	dev_dbg(&dev->client->dev, "chip_ver %u, role %u\n",
			dev->chip_ver, dev->role);
	return 0;

err_kfree:
	kfree(dev);
err:
	dev_dbg(&client->dev, "failed %d\n", ret);
	return ret;
}
