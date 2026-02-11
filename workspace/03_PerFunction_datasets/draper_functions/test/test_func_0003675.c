nm_device_bt_init (NMDeviceBt *self)
{
	NMDeviceBtPrivate *priv = NM_DEVICE_BT_GET_PRIVATE (self);
	gboolean mm_running;

	priv->dbus_mgr = nm_dbus_manager_get ();

	priv->mm_watch_id = g_signal_connect (priv->dbus_mgr,
	                                      NM_DBUS_MANAGER_NAME_OWNER_CHANGED,
	                                      G_CALLBACK (mm_name_owner_changed),
	                                      self);


	mm_running = nm_dbus_manager_name_has_owner (priv->dbus_mgr, MM_OLD_DBUS_SERVICE);
#if WITH_MODEM_MANAGER_1
	if (!mm_running)
		mm_running = nm_dbus_manager_name_has_owner (priv->dbus_mgr, MM_NEW_DBUS_SERVICE);
#endif
	set_mm_running (self, mm_running);
}
