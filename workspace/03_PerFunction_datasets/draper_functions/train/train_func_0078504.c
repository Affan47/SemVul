get_default_dir(void)
{
	const gchar *dir = NULL;
	GeanyProject *project = geany->app->project;

	if (project)
		dir = project->base_path;
	else
		dir = geany->prefs->default_open_path;

	if (NZV(dir))
		return utils_get_locale_from_utf8(dir);

	return g_get_current_dir();
}
