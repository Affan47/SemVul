axp288_charger_usb_get_property(struct power_supply *psy,
				    enum power_supply_property psp,
				    union power_supply_propval *val)
{
	struct axp288_chrg_info *info = power_supply_get_drvdata(psy);
	int ret = 0;

	mutex_lock(&info->lock);

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:

		if (info->otg.id_short) {
			val->intval = 0;
			break;
		}
		ret = axp288_charger_is_present(info);
		if (ret < 0)
			goto psy_get_prop_fail;
		info->present = ret;
		val->intval = info->present;
		break;
	case POWER_SUPPLY_PROP_ONLINE:

		if (info->otg.id_short) {
			val->intval = 0;
			break;
		}
		ret = axp288_charger_is_online(info);
		if (ret < 0)
			goto psy_get_prop_fail;
		info->online = ret;
		val->intval = info->online;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = axp288_get_charger_health(info);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		val->intval = info->cc * 1000;
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->intval = info->max_cc * 1000;
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		val->intval = info->cv * 1000;
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->intval = info->max_cv * 1000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		val->intval = info->inlmt * 1000;
		break;
	default:
		ret = -EINVAL;
		goto psy_get_prop_fail;
	}

psy_get_prop_fail:
	mutex_unlock(&info->lock);
	return ret;
}
