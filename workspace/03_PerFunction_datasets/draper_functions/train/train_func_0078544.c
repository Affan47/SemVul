on_profile_scoped (AnjutaProfile *profile, ProjectManagerPlugin *plugin)
{
	gchar *session_dir;


	project_manager_load_gbf (plugin);


	update_title (plugin, plugin->project_root_uri);


	session_dir = get_session_dir (plugin);
	g_return_if_fail (session_dir != NULL);


	plugin->session_by_me = TRUE;
	anjuta_shell_session_load (ANJUTA_PLUGIN (plugin)->shell,
							   session_dir, NULL);
	plugin->session_by_me = FALSE;
	g_free (session_dir);
}
