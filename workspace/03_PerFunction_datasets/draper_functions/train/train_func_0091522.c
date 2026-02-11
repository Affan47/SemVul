dac124s085_probe(struct spi_device *spi)
{
	struct dac124s085	*dac;
	struct dac124s085_led	*led;
	int i, ret;

	dac = devm_kzalloc(&spi->dev, sizeof(*dac), GFP_KERNEL);
	if (!dac)
		return -ENOMEM;

	spi->bits_per_word = 16;

	for (i = 0; i < ARRAY_SIZE(dac->leds); i++) {
		led		= dac->leds + i;
		led->id		= i;
		led->brightness	= LED_OFF;
		led->spi	= spi;
		snprintf(led->name, sizeof(led->name), "dac124s085-%d", i);
		spin_lock_init(&led->lock);
		INIT_WORK(&led->work, dac124s085_led_work);
		mutex_init(&led->mutex);
		led->ldev.name = led->name;
		led->ldev.brightness = LED_OFF;
		led->ldev.max_brightness = 0xfff;
		led->ldev.brightness_set = dac124s085_set_brightness;
		ret = led_classdev_register(&spi->dev, &led->ldev);
		if (ret < 0)
			goto eledcr;
	}

	spi_set_drvdata(spi, dac);

	return 0;

eledcr:
	while (i--)
		led_classdev_unregister(&dac->leds[i].ldev);

	return ret;
}
