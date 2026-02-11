file_type (GFile *file, const gchar *filename)
{
	GFile *child;
	GFileInfo *info;
	GFileType type;

	child = filename != NULL ? g_file_get_child (file, filename) : g_object_ref (file);


	info = g_file_query_info (child,
							  G_FILE_ATTRIBUTE_STANDARD_TYPE,
							  G_FILE_QUERY_INFO_NONE,
							  NULL,
							  NULL);
	if (info != NULL)
	{
		type = g_file_info_get_file_type (info);
		g_object_unref (info);
	}
	else
	{
		type = G_FILE_TYPE_UNKNOWN;
	}

	g_object_unref (child);

	return type;
}
