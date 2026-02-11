lp3944_configure(struct i2c_client *client,
			    struct lp3944_data *data,
			    struct lp3944_platform_data *pdata)
{
	int i, err = 0;

	for (i = 0; i < pdata->leds_size; i++) {
		struct lp3944_led *pled = &pdata->leds[i];
		struct lp3944_led_data *led = &data->leds[i];
		led->client = client;
		led->id = i;

		switch (pled->type) {

		case LP3944_LED_TYPE_LED:
		case LP3944_LED_TYPE_LED_INVERTED:
			led->type = pled->type;
			led->status = pled->status;
			led->ldev.name = pled->name;
			led->ldev.max_brightness = 1;
			led->ldev.brightness_set = lp3944_led_set_brightness;
			led->ldev.blink_set = lp3944_led_set_blink;
			led->ldev.flags = LED_CORE_SUSPENDRESUME;

			INIT_WORK(&led->work, lp3944_led_work);
			err = led_classdev_register(&client->dev, &led->ldev);
			if (err < 0) {
				dev_err(&client->dev,
					"couldn't register LED %s\n",
					led->ldev.name);
				goto exit;
			}


			led->ldev.brightness =
					(enum led_brightness) led->status;


			err = lp3944_led_set(led, led->status);
			if (err < 0) {
				dev_err(&client->dev,
					"%s couldn't set STATUS %d\n",
					led->ldev.name, led->status);
				goto exit;
			}
			break;

		case LP3944_LED_TYPE_NONE:
		default:
			break;

		}
	}
	return 0;

exit:
	if (i > 0)
		for (i = i - 1; i >= 0; i--)
			switch (pdata->leds[i].type) {

			case LP3944_LED_TYPE_LED:
			case LP3944_LED_TYPE_LED_INVERTED:
				led_classdev_unregister(&data->leds[i].ldev);
				cancel_work_sync(&data->leds[i].work);
				break;

			case LP3944_LED_TYPE_NONE:
			default:
				break;
			}

	return err;
}
