pk_plugin_get_installed_package_for_file (PkPlugin *plugin,
					  PkTransaction *transaction,
					  const gchar *filename)
{
	PkPackage *package = NULL;
	gchar **filenames;


	g_ptr_array_set_size (plugin->priv->list, 0);
	pk_backend_reset_job (plugin->backend, plugin->job);
	pk_backend_job_set_vfunc (plugin->job,
				  PK_BACKEND_SIGNAL_PACKAGE,
				  (PkBackendJobVFunc) pk_plugin_package_cb,
				  plugin);
	pk_backend_job_set_vfunc (plugin->job,
				  PK_BACKEND_SIGNAL_FINISHED,
				  (PkBackendJobVFunc) pk_plugin_finished_cb,
				  plugin);
	filenames = g_strsplit (filename, "|||", -1);
	pk_backend_search_files (plugin->backend,
				 plugin->job,
				 pk_bitfield_value (PK_FILTER_ENUM_INSTALLED),
				 filenames);


	g_main_loop_run (plugin->priv->loop);


	if (plugin->priv->list->len != 1) {
		g_warning ("not correct size, %i", plugin->priv->list->len);
		goto out;
	}


	package = g_ptr_array_index (plugin->priv->list, 0);
	if (package == NULL) {
		g_warning ("cannot get package");
		goto out;
	}
out:
	g_strfreev (filenames);
	return package;
}
