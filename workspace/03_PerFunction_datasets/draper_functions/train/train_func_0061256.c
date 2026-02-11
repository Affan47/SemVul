glade_window_open_project (GladeWindow *window,
			   const gchar *path)
{
	GladeProject *project;

	g_return_val_if_fail (GLADE_IS_WINDOW (window), FALSE);
	g_return_val_if_fail (path != NULL, FALSE);


	project = glade_app_get_project_by_path (path);
	if (project)
	{

		switch_to_project (window, project);
		return TRUE;
	}
	else
	{
		return open_project (window, path);
	}
}
