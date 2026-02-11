templates_replace_common(GString *tmpl, const gchar *fname,
							  GeanyFiletype *ft, const gchar *func_name)
{
	gchar *shortname;

	if (fname == NULL)
	{
		if (!ft->extension)
			shortname = g_strdup(GEANY_STRING_UNTITLED);
		else
			shortname = g_strconcat(GEANY_STRING_UNTITLED, ".", ft->extension, NULL);
	}
	else
		shortname = g_path_get_basename(fname);

	templates_replace_valist(tmpl,
		"{filename}", shortname,
		"{project}", app->project ? app->project->name : "",
		"{description}", app->project ? app->project->description : "",
		NULL);
	g_free(shortname);

	templates_replace_default_dates(tmpl);
	templates_replace_command(tmpl, fname, ft->name, func_name);


	templates_replace_valist(tmpl,
		"{ob}", "{",
		"{cb}", "}",
		NULL);
}
