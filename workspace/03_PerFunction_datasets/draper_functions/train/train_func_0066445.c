lm3630a_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct lm3630a_platform_data *pdata = dev_get_platdata(&client->dev);
	struct lm3630a_chip *pchip;
	int rval;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "fail : i2c functionality check\n");
		return -EOPNOTSUPP;
	}

	pchip = devm_kzalloc(&client->dev, sizeof(struct lm3630a_chip),
			     GFP_KERNEL);
	if (!pchip)
		return -ENOMEM;
	pchip->dev = &client->dev;

	pchip->regmap = devm_regmap_init_i2c(client, &lm3630a_regmap);
	if (IS_ERR(pchip->regmap)) {
		rval = PTR_ERR(pchip->regmap);
		dev_err(&client->dev, "fail : allocate reg. map: %d\n", rval);
		return rval;
	}

	i2c_set_clientdata(client, pchip);
	if (pdata == NULL) {
		pdata = devm_kzalloc(pchip->dev,
				     sizeof(struct lm3630a_platform_data),
				     GFP_KERNEL);
		if (pdata == NULL)
			return -ENOMEM;

		pdata->leda_ctrl = LM3630A_LEDA_ENABLE;
		pdata->ledb_ctrl = LM3630A_LEDB_ENABLE;
		pdata->leda_max_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->ledb_max_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->leda_init_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->ledb_init_brt = LM3630A_MAX_BRIGHTNESS;
	}
	pchip->pdata = pdata;


	rval = lm3630a_chip_init(pchip);
	if (rval < 0) {
		dev_err(&client->dev, "fail : init chip\n");
		return rval;
	}

	rval = lm3630a_backlight_register(pchip);
	if (rval < 0) {
		dev_err(&client->dev, "fail : backlight register.\n");
		return rval;
	}

	if (pdata->pwm_ctrl != LM3630A_PWM_DISABLE) {
		pchip->pwmd = devm_pwm_get(pchip->dev, "lm3630a-pwm");
		if (IS_ERR(pchip->pwmd)) {
			dev_err(&client->dev, "fail : get pwm device\n");
			return PTR_ERR(pchip->pwmd);
		}
	}
	pchip->pwmd->period = pdata->pwm_period;


	pchip->irq = client->irq;
	if (pchip->irq) {
		rval = lm3630a_intr_config(pchip);
		if (rval < 0)
			return rval;
	}
	dev_info(&client->dev, "LM3630A backlight register OK.\n");
	return 0;
}
