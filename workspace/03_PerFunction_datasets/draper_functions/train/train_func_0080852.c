up_device_unifying_refresh (UpDevice *device)
{
	gboolean ret;
	GError *error = NULL;
	GTimeVal timeval;
	HidppRefreshFlags refresh_flags;
	UpDeviceState state = UP_DEVICE_STATE_UNKNOWN;
	UpDeviceUnifying *unifying = UP_DEVICE_UNIFYING (device);
	UpDeviceUnifyingPrivate *priv = unifying->priv;
	double lux;


	refresh_flags = HIDPP_REFRESH_FLAGS_BATTERY;


	if (hidpp_device_get_version (priv->hidpp_device) == 0)
		refresh_flags |= HIDPP_REFRESH_FLAGS_VERSION;

	ret = hidpp_device_refresh (priv->hidpp_device,
				    refresh_flags,
				    &error);
	if (!ret) {
		g_warning ("failed to coldplug unifying device: %s",
			   error->message);
		g_error_free (error);
		goto out;
	}
	switch (hidpp_device_get_batt_status (priv->hidpp_device)) {
	case HIDPP_DEVICE_BATT_STATUS_CHARGING:
		state = UP_DEVICE_STATE_CHARGING;
		break;
	case HIDPP_DEVICE_BATT_STATUS_DISCHARGING:
		state = UP_DEVICE_STATE_DISCHARGING;
		break;
	case HIDPP_DEVICE_BATT_STATUS_CHARGED:
		state = UP_DEVICE_STATE_FULLY_CHARGED;
		break;
	default:
		break;
	}


	if (!hidpp_device_is_reachable (priv->hidpp_device)) {
		state = UP_DEVICE_STATE_UNKNOWN;
	}

	g_get_current_time (&timeval);
	lux = hidpp_device_get_luminosity (priv->hidpp_device);
	if (lux >= 0) {
		g_object_set (device, "luminosity", lux, NULL);
	}

	g_object_set (device,
		      "is-present", hidpp_device_is_reachable (priv->hidpp_device),
		      "percentage", (gdouble) hidpp_device_get_batt_percentage (priv->hidpp_device),
		      "state", state,
		      "update-time", (guint64) timeval.tv_sec,
		      NULL);
out:
	return TRUE;
}
