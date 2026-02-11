pk_plugin_finished_cb (PkBackendJob *job,
		       PkExitEnum exit_enum,
		       PkPlugin *plugin)
{
	if (!g_main_loop_is_running (plugin->priv->loop)) {
		g_warning ("loop not running");
		return;
	}
	g_main_loop_quit (plugin->priv->loop);
}
