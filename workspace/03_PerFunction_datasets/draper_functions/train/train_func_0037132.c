smb347_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	static char *battery[] = { "smb347-battery" };
	const struct smb347_charger_platform_data *pdata;
	struct power_supply_config mains_usb_cfg = {}, battery_cfg = {};
	struct device *dev = &client->dev;
	struct smb347_charger *smb;
	int ret;

	pdata = dev->platform_data;
	if (!pdata)
		return -EINVAL;

	if (!pdata->use_mains && !pdata->use_usb)
		return -EINVAL;

	smb = devm_kzalloc(dev, sizeof(*smb), GFP_KERNEL);
	if (!smb)
		return -ENOMEM;

	i2c_set_clientdata(client, smb);

	mutex_init(&smb->lock);
	smb->dev = &client->dev;
	smb->pdata = pdata;

	smb->regmap = devm_regmap_init_i2c(client, &smb347_regmap);
	if (IS_ERR(smb->regmap))
		return PTR_ERR(smb->regmap);

	ret = smb347_hw_init(smb);
	if (ret < 0)
		return ret;

	mains_usb_cfg.supplied_to = battery;
	mains_usb_cfg.num_supplicants = ARRAY_SIZE(battery);
	mains_usb_cfg.drv_data = smb;
	if (smb->pdata->use_mains) {
		smb->mains = power_supply_register(dev, &smb347_mains_desc,
						   &mains_usb_cfg);
		if (IS_ERR(smb->mains))
			return PTR_ERR(smb->mains);
	}

	if (smb->pdata->use_usb) {
		smb->usb = power_supply_register(dev, &smb347_usb_desc,
						 &mains_usb_cfg);
		if (IS_ERR(smb->usb)) {
			if (smb->pdata->use_mains)
				power_supply_unregister(smb->mains);
			return PTR_ERR(smb->usb);
		}
	}

	battery_cfg.drv_data = smb;
	smb->battery = power_supply_register(dev, &smb347_battery_desc,
					     &battery_cfg);
	if (IS_ERR(smb->battery)) {
		if (smb->pdata->use_usb)
			power_supply_unregister(smb->usb);
		if (smb->pdata->use_mains)
			power_supply_unregister(smb->mains);
		return PTR_ERR(smb->battery);
	}


	if (pdata->irq_gpio >= 0) {
		ret = smb347_irq_init(smb, client);
		if (ret < 0) {
			dev_warn(dev, "failed to initialize IRQ: %d\n", ret);
			dev_warn(dev, "disabling IRQ support\n");
		} else {
			smb347_irq_enable(smb);
		}
	}

	return 0;
}
