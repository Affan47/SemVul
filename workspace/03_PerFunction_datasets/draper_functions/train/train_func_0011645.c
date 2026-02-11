axp288_charger_extcon_evt_worker(struct work_struct *work)
{
	struct axp288_chrg_info *info =
	    container_of(work, struct axp288_chrg_info, cable.work);
	int ret, current_limit;
	bool changed = false;
	struct extcon_dev *edev = info->cable.edev;
	bool old_connected = info->cable.connected;


	if (extcon_get_cable_state(edev, AXP288_EXTCON_SLOW_CHARGER) > 0) {
		dev_dbg(&info->pdev->dev, "USB SDP charger  is connected");
		info->cable.connected = true;
		info->cable.chg_type = POWER_SUPPLY_TYPE_USB;
	} else if (extcon_get_cable_state(edev,
				AXP288_EXTCON_DOWNSTREAM_CHARGER) > 0) {
		dev_dbg(&info->pdev->dev, "USB CDP charger is connected");
		info->cable.connected = true;
		info->cable.chg_type = POWER_SUPPLY_TYPE_USB_CDP;
	} else if (extcon_get_cable_state(edev,
					AXP288_EXTCON_FAST_CHARGER) > 0) {
		dev_dbg(&info->pdev->dev, "USB DCP charger is connected");
		info->cable.connected = true;
		info->cable.chg_type = POWER_SUPPLY_TYPE_USB_DCP;
	} else {
		if (old_connected)
			dev_dbg(&info->pdev->dev, "USB charger disconnected");
		info->cable.connected = false;
		info->cable.chg_type = POWER_SUPPLY_TYPE_USB;
	}


	if (old_connected != info->cable.connected)
		changed = true;

	if (!changed)
		return;

	mutex_lock(&info->lock);

	if (info->is_charger_enabled && !info->cable.connected) {
		info->enable_charger = false;
		ret = axp288_charger_enable_charger(info, info->enable_charger);
		if (ret < 0)
			dev_err(&info->pdev->dev,
				"cannot disable charger (%d)", ret);

	} else if (!info->is_charger_enabled && info->cable.connected) {
		switch (info->cable.chg_type) {
		case POWER_SUPPLY_TYPE_USB:
			current_limit = ILIM_500MA;
			break;
		case POWER_SUPPLY_TYPE_USB_CDP:
			current_limit = ILIM_1500MA;
			break;
		case POWER_SUPPLY_TYPE_USB_DCP:
			current_limit = ILIM_2000MA;
			break;
		default:

			current_limit = 0;
			break;
		}


		ret = axp288_charger_set_vbus_inlmt(info, current_limit);
		if (ret < 0) {
			dev_err(&info->pdev->dev,
				"error setting current limit (%d)", ret);
		} else {
			info->enable_charger = (current_limit > 0);
			ret = axp288_charger_enable_charger(info,
							info->enable_charger);
			if (ret < 0)
				dev_err(&info->pdev->dev,
					"cannot enable charger (%d)", ret);
		}
	}

	if (changed)
		info->health = axp288_get_charger_health(info);

	mutex_unlock(&info->lock);

	if (changed)
		power_supply_changed(info->psy_usb);
}
