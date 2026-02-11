cd_plugin_config_enabled_sane_devices(CdPluginPrivate *priv)
{
	const gchar *argv[] = {COLORD_SANE_BINARY, NULL};
	GError *error = NULL;
	GPid colord_sane_pid;

	if (priv->scan_in_progress)
		return;
	g_spawn_async (NULL,
		       (gchar **) argv,
		       NULL,
		       G_SPAWN_DO_NOT_REAP_CHILD,
		       NULL,
		       NULL,
		       &colord_sane_pid,
		       &error);

	if (error != NULL) {
		g_warning ("CdPlugin: failed to spawn colord-sane helper: %s",
			   error->message);
		g_error_free (error);
		return;
	}

	priv->scan_in_progress = TRUE;
	g_child_watch_add (colord_sane_pid,
			   cd_plugin_colord_sane_finished_cb,
			   priv);
}
