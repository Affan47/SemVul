pm_gui_load_directory_page (PluginManagerGUI *pm_gui)
{
	GtkTreeIter iter;
	char * sys_plugins = g_build_filename (gnm_sys_lib_dir (), PLUGIN_SUBDIR, NULL);
	char * usr_plugins = (gnm_usr_dir (TRUE) == NULL ? NULL :
				g_build_filename (gnm_usr_dir (TRUE), PLUGIN_SUBDIR, NULL));
	char * go_plugins = go_plugins_get_plugin_dir ();
	GSList *plugin_dirs;
	gchar const *plugin_path_env;

	gtk_list_store_clear (pm_gui->model_directories);

	gtk_list_store_append (pm_gui->model_directories, &iter);
	gtk_list_store_set (pm_gui->model_directories, &iter,
			    DIR_NAME, sys_plugins,
			    DIR_IS_SYSTEM, TRUE,
			    -1);
	g_free (sys_plugins);
	gtk_list_store_append (pm_gui->model_directories, &iter);
	gtk_list_store_set (pm_gui->model_directories, &iter,
			    DIR_NAME, usr_plugins,
			    DIR_IS_SYSTEM, TRUE,
			    -1);
	g_free (usr_plugins);
	gtk_list_store_append (pm_gui->model_directories, &iter);
	gtk_list_store_set (pm_gui->model_directories, &iter,
			    DIR_NAME, go_plugins,
			    DIR_IS_SYSTEM, TRUE,
			    -1);
	g_free (go_plugins);

	plugin_path_env = g_getenv ("GNUMERIC_PLUGIN_PATH");
	if (plugin_path_env != NULL) {
		plugin_dirs = go_strsplit_to_slist (plugin_path_env, G_SEARCHPATH_SEPARATOR);
		pm_gui_load_directories (pm_gui, plugin_dirs, FALSE);
		g_slist_free_full (plugin_dirs, g_free);
	}
	pm_gui_load_directories (pm_gui, gnm_conf_get_plugins_extra_dirs (), TRUE);
}
