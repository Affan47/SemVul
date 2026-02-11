on_profile_descoped (AnjutaProfile *profile, ProjectManagerPlugin *plugin)
{
	DEBUG_PRINT ("%s", "Project profile descoped; Saving project session");


	g_return_if_fail (plugin->project_root_uri != NULL);


	project_manager_save_session (plugin);


	project_manager_unload_gbf (plugin);

	g_free (plugin->project_root_uri);
	if (plugin->project_file) g_object_unref (plugin->project_file);
	plugin->project_file = NULL;
	plugin->project_root_uri = NULL;

	update_title (ANJUTA_PLUGIN_PROJECT_MANAGER (plugin), NULL);
	anjuta_shell_remove_value (ANJUTA_PLUGIN (plugin)->shell,
						  IANJUTA_PROJECT_MANAGER_PROJECT_ROOT_URI, NULL);
}
