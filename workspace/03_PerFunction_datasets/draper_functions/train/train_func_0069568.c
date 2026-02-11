custom_file_changed (GFileMonitor *monitor,
                     GFile *file,
                     GFile *other_file,
                     GFileMonitorEvent event_type,
                     ECalBackendFilePrivate *priv)
{
	if (priv->refresh_cond)
		g_cond_signal (priv->refresh_cond);
}
