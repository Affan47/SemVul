ucb1400_core_probe(struct device *dev)
{
	int err;
	struct ucb1400 *ucb;
	struct ucb1400_ts ucb_ts;
	struct ucb1400_gpio ucb_gpio;
	struct snd_ac97 *ac97;
	struct ucb1400_pdata *pdata = dev_get_platdata(dev);

	memset(&ucb_ts, 0, sizeof(ucb_ts));
	memset(&ucb_gpio, 0, sizeof(ucb_gpio));

	ucb = kzalloc(sizeof(struct ucb1400), GFP_KERNEL);
	if (!ucb) {
		err = -ENOMEM;
		goto err;
	}

	dev_set_drvdata(dev, ucb);

	ac97 = to_ac97_t(dev);

	ucb_ts.id = ucb1400_reg_read(ac97, UCB_ID);
	if (ucb_ts.id != UCB_ID_1400) {
		err = -ENODEV;
		goto err0;
	}


	ucb_gpio.ac97 = ac97;
	if (pdata) {
		ucb_gpio.gpio_setup = pdata->gpio_setup;
		ucb_gpio.gpio_teardown = pdata->gpio_teardown;
		ucb_gpio.gpio_offset = pdata->gpio_offset;
	}
	ucb->ucb1400_gpio = platform_device_alloc("ucb1400_gpio", -1);
	if (!ucb->ucb1400_gpio) {
		err = -ENOMEM;
		goto err0;
	}
	err = platform_device_add_data(ucb->ucb1400_gpio, &ucb_gpio,
					sizeof(ucb_gpio));
	if (err)
		goto err1;
	err = platform_device_add(ucb->ucb1400_gpio);
	if (err)
		goto err1;


	ucb_ts.ac97 = ac97;

	if (pdata != NULL && pdata->irq >= 0)
		ucb_ts.irq = pdata->irq;
	else
		ucb_ts.irq = -1;

	ucb->ucb1400_ts = platform_device_alloc("ucb1400_ts", -1);
	if (!ucb->ucb1400_ts) {
		err = -ENOMEM;
		goto err2;
	}
	err = platform_device_add_data(ucb->ucb1400_ts, &ucb_ts,
					sizeof(ucb_ts));
	if (err)
		goto err3;
	err = platform_device_add(ucb->ucb1400_ts);
	if (err)
		goto err3;

	return 0;

err3:
	platform_device_put(ucb->ucb1400_ts);
err2:
	platform_device_del(ucb->ucb1400_gpio);
err1:
	platform_device_put(ucb->ucb1400_gpio);
err0:
	kfree(ucb);
err:
	return err;
}
