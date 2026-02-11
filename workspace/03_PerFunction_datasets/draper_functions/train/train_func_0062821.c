amp_package_node_load (AmpNode *node, AmpNode *parent, AmpProject *project, GError **error)
{
	GList* deps;
	GList* dep;
	GList* include_dirs = NULL;

	deps = anjuta_pkg_config_list_dependencies (anjuta_project_node_get_name (ANJUTA_PROJECT_NODE (node)),
	                                            error);
	for (dep = deps; dep != NULL; dep = g_list_next (dep))
	{

		AnjutaProjectNode *pkg;

		pkg = ANJUTA_PROJECT_NODE (amp_package_node_new (dep->data));
		anjuta_project_node_append (ANJUTA_PROJECT_NODE (node), pkg);
	}
	anjuta_util_glist_strings_free (deps);

	if (*error != NULL)
	{
		g_warning ("Error getting dependencies: %s", (*error)->message);
		g_error_free (*error);
		*error = NULL;
	}

	if ((include_dirs = anjuta_pkg_config_get_directories (anjuta_project_node_get_name (ANJUTA_PROJECT_NODE (node)),
	                                                       TRUE, error)))
	{
		GList* include_dir;

		for (include_dir = include_dirs; include_dir != NULL; include_dir = g_list_next (include_dir))
		{
			GList* children = NULL;
			GList* file = NULL;
			GFile* dir = g_file_new_for_path (include_dir->data);

			anjuta_util_list_all_dir_children (&children, dir);
			for (file = g_list_first (children); file != NULL; file = g_list_next (file))
			{

				AnjutaProjectNode *source;

				source = amp_node_new_valid (ANJUTA_PROJECT_NODE (parent), ANJUTA_PROJECT_SOURCE, (GFile *)file->data, NULL, NULL);
				anjuta_project_node_append (ANJUTA_PROJECT_NODE (node), source);
				g_object_unref ((GObject *)file->data);
			}
			g_list_free (children);
			g_object_unref (dir);
		}
	}
	anjuta_util_glist_strings_free (include_dirs);

	return TRUE;
}
