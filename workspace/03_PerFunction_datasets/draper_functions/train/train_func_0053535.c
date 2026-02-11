bat_set_property(struct power_supply *psy,
				enum power_supply_property psp,
				const union power_supply_propval *val)
{
	int level;

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		level = val->intval;
		if (level < 0 || level > BAT_CHARGE_LIMIT_MAX)
			return -EINVAL;
		if (ec_write(BAT_CHARGE_LIMIT, level) < 0)
			return -EIO;
		break;
	default:
		break;
	}
	return 0;
}
