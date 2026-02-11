ds2404_gpio_map(struct ds2404 *chip, struct platform_device *pdev,
			  struct ds2404_platform_data *pdata)
{
	int i, err;

	ds2404_gpio[DS2404_RST].gpio = pdata->gpio_rst;
	ds2404_gpio[DS2404_CLK].gpio = pdata->gpio_clk;
	ds2404_gpio[DS2404_DQ].gpio = pdata->gpio_dq;

	for (i = 0; i < ARRAY_SIZE(ds2404_gpio); i++) {
		err = gpio_request(ds2404_gpio[i].gpio, ds2404_gpio[i].name);
		if (err) {
			dev_err(&pdev->dev, "error mapping gpio %s: %d\n",
				ds2404_gpio[i].name, err);
			goto err_request;
		}
		if (i != DS2404_DQ)
			gpio_direction_output(ds2404_gpio[i].gpio, 1);
	}

	chip->gpio = ds2404_gpio;
	return 0;

err_request:
	while (--i >= 0)
		gpio_free(ds2404_gpio[i].gpio);
	return err;
}
