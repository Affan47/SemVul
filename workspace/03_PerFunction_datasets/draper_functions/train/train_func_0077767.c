brasero_medium_monitor_get_drive (BraseroMediumMonitor *monitor,
				  const gchar *device)
{
	GSList *iter;
	BraseroMediumMonitorPrivate *priv;

	g_return_val_if_fail (monitor != NULL, NULL);
	g_return_val_if_fail (device != NULL, NULL);
	g_return_val_if_fail (BRASERO_IS_MEDIUM_MONITOR (monitor), NULL);

	priv = BRASERO_MEDIUM_MONITOR_PRIVATE (monitor);
	for (iter = priv->drives; iter; iter = iter->next) {
		BraseroDrive *drive;
		const gchar *drive_device;

		drive = iter->data;
		drive_device = brasero_drive_get_device (drive);
		if (drive_device && !strcmp (drive_device, device)) {
			g_object_ref (drive);
			return drive;
		}
	}

	return NULL;
}
