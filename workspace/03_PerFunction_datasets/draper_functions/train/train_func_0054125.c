free_smartphone_device_power_status_from_string (const char* str, GError** error) {
	FreeSmartphoneDevicePowerStatus value = 0;
	if (strcmp (str, "charging") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_CHARGING;
	} else if (strcmp (str, "discharging") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_DISCHARGING;
	} else if (strcmp (str, "full") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_FULL;
	} else if (strcmp (str, "empty") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_EMPTY;
	} else if (strcmp (str, "critical") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_CRITICAL;
	} else if (strcmp (str, "critical") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_REMOVED;
	} else if (strcmp (str, "unknown") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_UNKNOWN;
	} else if (strcmp (str, "online") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_ONLINE;
	} else if (strcmp (str, "offline") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_OFFLINE;
	} else if (strcmp (str, "ac") == 0) {
		value = FREE_SMARTPHONE_DEVICE_POWER_STATUS_AC;
	} else {
		g_set_error (error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "Invalid value for enum `FreeSmartphoneDevicePowerStatus'");
	}
	return value;
}
