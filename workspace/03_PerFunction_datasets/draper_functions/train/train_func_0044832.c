da9150_fg_get_prop(struct power_supply *psy,
			      enum power_supply_property psp,
			      union power_supply_propval *val)
{
	struct da9150_fg *fg = dev_get_drvdata(psy->dev.parent);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = da9150_fg_capacity(fg, val);
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9150_fg_current_avg(fg, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = da9150_fg_voltage_avg(fg, val);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = da9150_fg_charge_full(fg, val);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		ret = da9150_fg_temp(fg, val);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
