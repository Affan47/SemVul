finalize (GObject *obj)
{
	gint i;
	BasicAutotoolsPlugin *ba_plugin = ANJUTA_PLUGIN_BASIC_AUTOTOOLS (obj);

	for (i = 0; i < IANJUTA_BUILDABLE_N_COMMANDS; i++)
	{
		g_free (ba_plugin->commands[i]);
		ba_plugin->commands[i] = NULL;
	}

	if (ba_plugin->fm_current_file != NULL) g_object_unref (ba_plugin->fm_current_file);
	if (ba_plugin->pm_current_file != NULL) g_object_unref (ba_plugin->pm_current_file);
	if (ba_plugin->current_editor_file != NULL) g_object_unref (ba_plugin->current_editor_file);
	if (ba_plugin->project_root_dir != NULL) g_object_unref (ba_plugin->project_root_dir);
	if (ba_plugin->project_build_dir != NULL) g_object_unref (ba_plugin->project_build_dir);
	g_free (ba_plugin->program_args);
	build_configuration_list_free (ba_plugin->configurations);

	ba_plugin->fm_current_file = NULL;
	ba_plugin->pm_current_file = NULL;
	ba_plugin->current_editor_file = NULL;
	ba_plugin->project_root_dir = NULL;
	ba_plugin->project_build_dir = NULL;
	ba_plugin->program_args = NULL;
	ba_plugin->configurations = NULL;

	G_OBJECT_CLASS (parent_class)->finalize (obj);
}
