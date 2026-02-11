lm3530_brightness_set(struct led_classdev *led_cdev,
				     enum led_brightness brt_val)
{
	int err;
	struct lm3530_data *drvdata =
	    container_of(led_cdev, struct lm3530_data, led_dev);
	struct lm3530_platform_data *pdata = drvdata->pdata;
	struct lm3530_pwm_data *pwm = &pdata->pwm_data;
	u8 max_brightness = led_cdev->max_brightness;

	switch (drvdata->mode) {
	case LM3530_BL_MODE_MANUAL:

		if (!drvdata->enable) {
			err = lm3530_init_registers(drvdata);
			if (err) {
				dev_err(&drvdata->client->dev,
					"Register Init failed: %d\n", err);
				break;
			}
		}


		err = i2c_smbus_write_byte_data(drvdata->client,
				LM3530_BRT_CTRL_REG, brt_val);
		if (err)
			dev_err(&drvdata->client->dev,
				"Unable to set brightness: %d\n", err);
		else
			drvdata->brightness = brt_val;

		if (brt_val == 0)
			lm3530_led_disable(drvdata);
		break;
	case LM3530_BL_MODE_ALS:
		break;
	case LM3530_BL_MODE_PWM:
		if (pwm->pwm_set_intensity)
			pwm->pwm_set_intensity(brt_val, max_brightness);
		break;
	default:
		break;
	}
}
