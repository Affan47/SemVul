lp872x_init_dvs(struct lp872x *lp)
{
	int ret, gpio;
	struct lp872x_dvs *dvs = lp->pdata ? lp->pdata->dvs : NULL;
	enum lp872x_dvs_state pinstate;
	u8 mask[] = { LP8720_EXT_DVS_M, LP8725_DVS1_M | LP8725_DVS2_M };
	u8 default_dvs_mode[] = { LP8720_DEFAULT_DVS, LP8725_DEFAULT_DVS };

	if (!dvs)
		goto set_default_dvs_mode;

	gpio = dvs->gpio;
	if (!gpio_is_valid(gpio)) {
		dev_warn(lp->dev, "invalid gpio: %d\n", gpio);
		goto set_default_dvs_mode;
	}

	pinstate = dvs->init_state;
	ret = devm_gpio_request_one(lp->dev, gpio, pinstate, "LP872X DVS");
	if (ret) {
		dev_err(lp->dev, "gpio request err: %d\n", ret);
		return ret;
	}

	lp->dvs_pin = pinstate;
	lp->dvs_gpio = gpio;

	return 0;

set_default_dvs_mode:
	return lp872x_update_bits(lp, LP872X_GENERAL_CFG, mask[lp->chipid],
				default_dvs_mode[lp->chipid]);
}
