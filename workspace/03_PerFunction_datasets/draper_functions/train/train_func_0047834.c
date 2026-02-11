firmware_dir_changed (GFileMonitor *monitor,
                      GFile *file,
                      GFile *other_file,
                      GFileMonitorEvent event_type,
                      gpointer user_data)
{
	NMManager *self = NM_MANAGER (user_data);
	NMManagerPrivate *priv = NM_MANAGER_GET_PRIVATE (self);

	switch (event_type) {
	case G_FILE_MONITOR_EVENT_CREATED:
	case G_FILE_MONITOR_EVENT_CHANGED:
#if GLIB_CHECK_VERSION(2,23,4)
	case G_FILE_MONITOR_EVENT_MOVED:
#endif
	case G_FILE_MONITOR_EVENT_ATTRIBUTE_CHANGED:
	case G_FILE_MONITOR_EVENT_CHANGES_DONE_HINT:
		if (!priv->fw_changed_id) {
			priv->fw_changed_id = g_timeout_add_seconds (4, handle_firmware_changed, self);
			nm_log_info (LOGD_CORE, "kernel firmware directory '%s' changed",
			             KERNEL_FIRMWARE_DIR);
		}
		break;
	default:
		break;
	}
}
