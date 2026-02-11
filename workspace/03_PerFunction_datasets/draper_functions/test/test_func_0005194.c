mn88473_init(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct mn88473_dev *dev = i2c_get_clientdata(client);
	int ret, len, remaining;
	const struct firmware *fw = NULL;
	u8 *fw_file = MN88473_FIRMWARE;
	unsigned int tmp;

	dev_dbg(&client->dev, "\n");


	dev->warm = false;


	ret = regmap_read(dev->regmap[0], 0xf5, &tmp);
	if (ret)
		goto err;

	if (!(tmp & 0x1)) {
		dev_info(&client->dev, "firmware already running\n");
		dev->warm = true;
		return 0;
	}


	ret = request_firmware(&fw, fw_file, &client->dev);
	if (ret) {
		dev_err(&client->dev, "firmare file '%s' not found\n", fw_file);
		goto err_request_firmware;
	}

	dev_info(&client->dev, "downloading firmware from file '%s'\n",
		 fw_file);

	ret = regmap_write(dev->regmap[0], 0xf5, 0x03);
	if (ret)
		goto err;

	for (remaining = fw->size; remaining > 0;
			remaining -= (dev->i2c_wr_max - 1)) {
		len = remaining;
		if (len > (dev->i2c_wr_max - 1))
			len = dev->i2c_wr_max - 1;

		ret = regmap_bulk_write(dev->regmap[0], 0xf6,
					&fw->data[fw->size - remaining], len);
		if (ret) {
			dev_err(&client->dev, "firmware download failed=%d\n",
				ret);
			goto err;
		}
	}


	ret = regmap_read(dev->regmap[0], 0xf8, &tmp);
	if (ret) {
		dev_err(&client->dev,
				"parity reg read failed=%d\n", ret);
		goto err;
	}
	if (tmp & 0x10) {
		dev_err(&client->dev,
				"firmware parity check failed=0x%x\n", tmp);
		goto err;
	}
	dev_err(&client->dev, "firmware parity check succeeded=0x%x\n", tmp);

	ret = regmap_write(dev->regmap[0], 0xf5, 0x00);
	if (ret)
		goto err;

	release_firmware(fw);
	fw = NULL;


	dev->warm = true;

	return 0;

err:
	release_firmware(fw);
err_request_firmware:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}
