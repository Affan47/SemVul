up_device_perhaps_changed_cb (GObject *object, GParamSpec *pspec, UpDevice *device)
{
	g_return_if_fail (UP_IS_DEVICE (device));


	if (device->priv->during_coldplug)
		return;


	up_history_set_state (device->priv->history, device->priv->state);
	up_history_set_charge_data (device->priv->history, device->priv->percentage);
	up_history_set_rate_data (device->priv->history, device->priv->energy_rate);
	up_history_set_time_full_data (device->priv->history, device->priv->time_to_full);
	up_history_set_time_empty_data (device->priv->history, device->priv->time_to_empty);


	g_debug ("emitting changed on %s", device->priv->native_path);
	g_signal_emit (device, signals[SIGNAL_CHANGED], 0);
}
