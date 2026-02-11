smbb_chg_gone_handler(int irq, void *_data)
{
	struct smbb_charger *chg = _data;

	smbb_set_line_flag(chg, irq, STATUS_CHG_GONE);
	power_supply_changed(chg->bat_psy);
	power_supply_changed(chg->usb_psy);
	if (!chg->dc_disabled)
		power_supply_changed(chg->dc_psy);

	return IRQ_HANDLED;
}
