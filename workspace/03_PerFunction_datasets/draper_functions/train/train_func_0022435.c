pm860x_batt_get_prop(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);
	int data;
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = info->present;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = calc_capacity(info, &data);
		if (ret)
			return ret;
		if (data < 0)
			data = 0;
		else if (data > 100)
			data = 100;

		if (!info->present)
			data = 100;
		val->intval = data;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:

		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (ret)
			return ret;
		val->intval = data * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:

		ret = calc_ocv(info, &data);
		if (ret)
			return ret;
		val->intval = data * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = measure_current(info, &data);
		if (ret)
			return ret;
		val->intval = data;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		if (info->present) {
			ret = measure_temp(info, &data);
			if (ret)
				return ret;
			data *= 10;
		} else {

			data = 250;
		}
		val->intval = data;
		break;
	default:
		return -ENODEV;
	}
	return 0;
}
