wm8350_bat_check_health(struct wm8350 *wm8350)
{
	u16 reg;

	if (wm8350_read_battery_uvolts(wm8350) < 2850000)
		return POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;

	reg = wm8350_reg_read(wm8350, WM8350_CHARGER_OVERRIDES);
	if (reg & WM8350_CHG_BATT_HOT_OVRDE)
		return POWER_SUPPLY_HEALTH_OVERHEAT;

	if (reg & WM8350_CHG_BATT_COLD_OVRDE)
		return POWER_SUPPLY_HEALTH_COLD;

	return POWER_SUPPLY_HEALTH_GOOD;
}
