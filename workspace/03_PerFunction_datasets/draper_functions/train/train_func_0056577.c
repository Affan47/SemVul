signal_power_supply_changed(struct power_supply *psy)
{
	if (module_initialized)
		power_supply_changed(psy);
}
