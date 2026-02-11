xproject_remove_file(const gchar *path)
{
	TMWorkObject *tm_obj;

	debug("%s path=%s\n", __FUNCTION__, path);

	if (!g_current_project)
		return FALSE;

	tm_obj = (TMWorkObject *) g_hash_table_lookup(g_current_project->tags, path);
	if (tm_obj)
	{
		tm_workspace_remove_object(tm_obj, FALSE, FALSE);
	}

	if (geany_project_remove_file(g_current_project, path))
	{
		sidebar_refresh();
		return TRUE;
	}
	return FALSE;
}
