get_vcs_plugin(AnjutaFileManager* file_manager, const gchar* root_uri)
{
	typedef struct
	{
		const gchar* file;
		const gchar* name;
	} VcsSystem;
	VcsSystem vcs_systems[] = {
		{".svn", "Subversion"},
		{".git", "Git"},
		{NULL, NULL}
	};

	gint i;
	const gchar* vcs_system = NULL;
	IAnjutaVcs* ivcs = NULL;
	for (i = 0; vcs_systems[i].name != NULL; i++)
	{
		gchar* vcs_uri = g_build_filename (root_uri, vcs_systems[i].file, NULL);
		GFile* vcs_file = g_file_new_for_uri (vcs_uri);
		if (g_file_query_exists(vcs_file, NULL))
		{
			vcs_system = vcs_systems[i].name;
		}
		g_free (vcs_uri);
		g_object_unref (vcs_file);
		if (vcs_system)
			break;
	}

	if (vcs_system)
	{

		AnjutaPluginManager* plugin_manager = anjuta_shell_get_plugin_manager (ANJUTA_PLUGIN(file_manager)->shell, NULL);
		GList* plugin_handles = anjuta_plugin_manager_query (plugin_manager,
														   "Anjuta Plugin",
														   "Interfaces",
														   "IAnjutaVcs",
														   "Vcs",
														   "System",
														   vcs_system, NULL);
		if (plugin_handles)
		{
			ivcs = IANJUTA_VCS(anjuta_plugin_manager_get_plugin_by_handle (plugin_manager,
			                                                               (AnjutaPluginHandle *)plugin_handles->data));

			g_signal_connect (G_OBJECT (ivcs), "status_changed",
			                  G_CALLBACK (refresh_signal_cb),
			                  file_manager);

			g_list_free (plugin_handles);
		}
	}
	return ivcs;
}
