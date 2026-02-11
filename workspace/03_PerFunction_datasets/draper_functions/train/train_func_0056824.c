set_active_ap (NMDeviceWifi *self, NMAccessPoint *new_ap)
{
	NMDeviceWifiPrivate *priv;
	char *old_path = NULL;
	NMAccessPoint *old_ap;

	g_return_if_fail (NM_IS_DEVICE_WIFI (self));

	priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	old_ap = priv->current_ap;

	if (old_ap) {
		old_path = g_strdup (nm_ap_get_dbus_path (old_ap));
		priv->current_ap = NULL;
	}

	if (new_ap) {
		priv->current_ap = g_object_ref (new_ap);


		priv->ap_list = g_slist_remove (priv->ap_list, new_ap);
		priv->ap_list = g_slist_prepend (priv->ap_list, new_ap);


		update_seen_bssids_cache (self, priv->current_ap);
	}


	if (old_ap)
		g_object_unref (old_ap);


	if (   (!old_path && new_ap)
	    || (old_path && !new_ap)
	    || (old_path && new_ap && strcmp (old_path, nm_ap_get_dbus_path (new_ap))))
		g_object_notify (G_OBJECT (self), NM_DEVICE_WIFI_ACTIVE_ACCESS_POINT);

	g_free (old_path);
}
