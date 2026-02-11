up_device_supply_push_new_energy (UpDeviceSupply *supply, gdouble energy)
{
	guint first = supply->priv->energy_old_first;
	guint new_position = (first + UP_DEVICE_SUPPLY_ENERGY_OLD_LENGTH - 1) %
		UP_DEVICE_SUPPLY_ENERGY_OLD_LENGTH;


	if (supply->priv->energy_old[first] != energy) {
		supply->priv->energy_old[new_position] = energy;
		g_get_current_time (&supply->priv->energy_old_timespec[new_position]);
		supply->priv->energy_old_first = new_position;
		return TRUE;
	}

	return FALSE;
}
