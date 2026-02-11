lp8727_register_psy(struct lp8727_chg *pchg)
{
	struct power_supply_config psy_cfg = {};
	struct lp8727_psy *psy;

	psy = devm_kzalloc(pchg->dev, sizeof(*psy), GFP_KERNEL);
	if (!psy)
		return -ENOMEM;

	pchg->psy = psy;

	psy_cfg.supplied_to = battery_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(battery_supplied_to);

	psy->ac = power_supply_register(pchg->dev, &lp8727_ac_desc, &psy_cfg);
	if (IS_ERR(psy->ac))
		goto err_psy_ac;

	psy->usb = power_supply_register(pchg->dev, &lp8727_usb_desc,
					 &psy_cfg);
	if (IS_ERR(psy->usb))
		goto err_psy_usb;

	psy->batt = power_supply_register(pchg->dev, &lp8727_batt_desc, NULL);
	if (IS_ERR(psy->batt))
		goto err_psy_batt;

	return 0;

err_psy_batt:
	power_supply_unregister(psy->usb);
err_psy_usb:
	power_supply_unregister(psy->ac);
err_psy_ac:
	return -EPERM;
}
