access_point_removed (NMObject *self_obj, NMObject *ap_obj)
{
	NMDeviceWifi *self = NM_DEVICE_WIFI (self_obj);
	NMDeviceWifiPrivate *priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	NMAccessPoint *ap = NM_ACCESS_POINT (ap_obj);

	if (ap == priv->active_ap) {
		g_object_unref (priv->active_ap);
		priv->active_ap = NULL;
		_nm_object_queue_notify (NM_OBJECT (self), NM_DEVICE_WIFI_ACTIVE_ACCESS_POINT);

		priv->rate = 0;
		_nm_object_queue_notify (NM_OBJECT (self), NM_DEVICE_WIFI_BITRATE);
	}

	g_signal_emit (self, signals[ACCESS_POINT_REMOVED], 0, ap);
}
