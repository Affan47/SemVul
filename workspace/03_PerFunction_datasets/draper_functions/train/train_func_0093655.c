nm_netlink_monitor_get (void)
{
	static NMNetlinkMonitor *singleton = NULL;
	GError *error = NULL;

	if (!singleton) {
		singleton = (NMNetlinkMonitor *) g_object_new (NM_TYPE_NETLINK_MONITOR, NULL);
		g_return_val_if_fail (singleton != NULL, NULL);

		if (nm_netlink_monitor_open_connection (singleton, &error)) {
			nm_netlink_monitor_attach (singleton);

			nm_netlink_monitor_request_status (singleton);
		} else {
			nm_log_warn (LOGD_HW, "Failed to connect to netlink: (%d) %s",
			             error ? error->code : 0,
			             (error && error->message) ? error->message : "(unknown)");
			g_clear_error (&error);

			g_object_unref (singleton);
			singleton = NULL;
		}
	} else
		g_object_ref (singleton);

	return singleton;
}
