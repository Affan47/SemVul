ltr501_drdy(struct ltr501_data *data, u8 drdy_mask)
{
	int tries = 100;
	int ret, status;

	while (tries--) {
		ret = regmap_read(data->regmap, LTR501_ALS_PS_STATUS, &status);
		if (ret < 0)
			return ret;
		if ((status & drdy_mask) == drdy_mask)
			return 0;
		msleep(25);
	}

	dev_err(&data->client->dev, "ltr501_drdy() failed, data not ready\n");
	return -EIO;
}
