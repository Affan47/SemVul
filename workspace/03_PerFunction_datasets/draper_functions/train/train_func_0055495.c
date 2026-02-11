is_gedit_user_style_scheme (const gchar *scheme_id)
{
	GtkSourceStyleSchemeManager *manager;
	GtkSourceStyleScheme *scheme;
	gboolean res = FALSE;

	manager = gtk_source_style_scheme_manager_get_default ();
	scheme = gtk_source_style_scheme_manager_get_scheme (manager, scheme_id);
	if (scheme != NULL)
	{
		const gchar *filename;

		filename = gtk_source_style_scheme_get_filename (scheme);
		if (filename != NULL)
		{
			res = g_str_has_prefix (filename, gedit_dirs_get_user_styles_dir ());
		}
	}

	return res;
}
