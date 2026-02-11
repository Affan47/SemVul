amp_project_unload (AmpProject *project)
{

	amp_project_clear (project);


	if (project->groups) g_hash_table_remove_all (project->groups);
	if (project->files != NULL)
	{
		GList *list;

		for (list = project->files; list != NULL; list = g_list_delete_link (list, list))
		{
			g_object_weak_unref (G_OBJECT (list->data), remove_config_file, project);
		}
		project->files = NULL;
	}
	if (project->configs) g_hash_table_remove_all (project->configs);


	if (project->am_space_list) anjuta_token_style_free (project->am_space_list);
	if (project->ac_space_list) anjuta_token_style_free (project->ac_space_list);
	if (project->arg_list) anjuta_token_style_free (project->arg_list);
}
