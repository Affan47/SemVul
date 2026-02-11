sii9234_reset(struct sii9234_context *ctx)
{
	struct i2c_client *client = ctx->client;
	struct device *dev = &client->dev;
	int ret, tries;

	gpio_direction_output(ctx->gpio_n_reset, 1);
	mdelay(1);
	gpio_direction_output(ctx->gpio_n_reset, 0);
	mdelay(1);
	gpio_direction_output(ctx->gpio_n_reset, 1);
	mdelay(1);


	ret = sii9234_writeb(client, 0xc7, 0);
	if (ret < 0) {
		dev_err(dev, "failed to set TTPI mode\n");
		return ret;
	}
	for (tries = 0; tries < 100 ; ++tries) {
		ret = sii9234_readb(client, 0x1b);
		if (ret > 0)
			break;
		if (ret < 0) {
			dev_err(dev, "failed to reset device\n");
			return -EIO;
		}
		mdelay(1);
	}
	if (tries == 100) {
		dev_err(dev, "maximal number of tries reached\n");
		return -EIO;
	}

	return 0;
}
