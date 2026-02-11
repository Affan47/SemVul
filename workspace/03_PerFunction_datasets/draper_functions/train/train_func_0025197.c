handle_uevent (GUdevClient *client,
               const char *action,
               GUdevDevice *device,
               gpointer user_data)
{
	NMUdevManager *self = NM_UDEV_MANAGER (user_data);
	const char *subsys;

	g_return_if_fail (action != NULL);


	subsys = g_udev_device_get_subsystem (device);
	g_return_if_fail (subsys != NULL);

	nm_log_dbg (LOGD_HW, "UDEV event: action '%s' subsys '%s' device '%s'",
	            action, subsys, g_udev_device_get_name (device));

	g_return_if_fail (!strcmp (subsys, "rfkill") || !strcmp (subsys, "net") ||
	                  !strcmp (subsys, "atm"));

	if (!strcmp (action, "add")) {
		if (!strcmp (subsys, "rfkill"))
			rfkill_add (self, device);
		else if (!strcmp (subsys, "net"))
			net_add (self, device);
		else if (!strcmp (subsys, "atm"))
			adsl_add (self, device);
	} else if (!strcmp (action, "remove")) {
		if (!strcmp (subsys, "rfkill"))
			rfkill_remove (self, device);
		else if (!strcmp (subsys, "net"))
			net_remove (self, device);
		else if (!strcmp (subsys, "atm"))
			adsl_remove (self, device);
	}

	recheck_killswitches (self);
}
