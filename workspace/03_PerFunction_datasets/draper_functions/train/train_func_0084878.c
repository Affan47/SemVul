pm860x_batt_set_prop(struct power_supply *psy,
				       enum power_supply_property psp,
				       const union power_supply_propval *val)
{
	struct pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		clear_ccnt(info, &ccnt_data);
		info->start_soc = 100;
		dev_dbg(info->dev, "chg done, update soc = %d\n",
			info->start_soc);
		break;
	default:
		return -EPERM;
	}

	return 0;
}
