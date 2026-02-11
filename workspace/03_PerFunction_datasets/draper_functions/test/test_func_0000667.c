wm1250_ev1_pdata(struct i2c_client *i2c)
{
	struct wm1250_ev1_pdata *pdata = dev_get_platdata(&i2c->dev);
	struct wm1250_priv *wm1250;
	int i, ret;

	if (!pdata)
		return 0;

	wm1250 = devm_kzalloc(&i2c->dev, sizeof(*wm1250), GFP_KERNEL);
	if (!wm1250) {
		ret = -ENOMEM;
		goto err;
	}

	for (i = 0; i < ARRAY_SIZE(wm1250->gpios); i++) {
		wm1250->gpios[i].gpio = pdata->gpios[i];
		wm1250->gpios[i].label = wm1250_gpio_names[i];
		wm1250->gpios[i].flags = GPIOF_OUT_INIT_LOW;
	}
	wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL0].flags = GPIOF_OUT_INIT_HIGH;
	wm1250->gpios[WM1250_EV1_GPIO_CLK_SEL1].flags = GPIOF_OUT_INIT_HIGH;

	ret = gpio_request_array(wm1250->gpios, ARRAY_SIZE(wm1250->gpios));
	if (ret != 0) {
		dev_err(&i2c->dev, "Failed to get GPIOs: %d\n", ret);
		goto err;
	}

	dev_set_drvdata(&i2c->dev, wm1250);

	return ret;

err:
	return ret;
}
