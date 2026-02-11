update_title (ProjectManagerPlugin* plugin, const gchar *project_uri)
{
	AnjutaStatus *status;
	status = anjuta_shell_get_status (ANJUTA_PLUGIN (plugin)->shell, NULL);
	if (project_uri)
	{
		GFileInfo *file_info;
		GFile *file;

		file = g_file_new_for_uri (project_uri);
		file_info = g_file_query_info (file,
			G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME,
			G_FILE_QUERY_INFO_NONE,
			NULL,
			NULL);
		if (file_info)
		{
			gchar *dispname;
			gchar *ext;

			dispname = g_strdup (
				g_file_info_get_display_name (file_info));
			ext = strrchr (dispname, '.');
			if (ext)
				*ext = '\0';
			anjuta_status_set_title (status, dispname);
			g_free (dispname);
			g_object_unref (file_info);
		}

		g_object_unref (file);
	}
	else
	{
		anjuta_status_set_title (status, NULL);
	}
}
