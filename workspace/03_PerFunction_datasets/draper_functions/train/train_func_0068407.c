nautilus_ensure_unique_file_name (const char *directory_uri,
				  const char *base_name,
				  const char *extension)
{
	GFileInfo *info;
	char *filename;
	GFile *dir, *child;
	int copy;
	char *res;

	dir = g_file_new_for_uri (directory_uri);

	info = g_file_query_info (dir, G_FILE_ATTRIBUTE_STANDARD_TYPE, 0, NULL, NULL);
	if (info == NULL) {
		g_object_unref (dir);
		return NULL;
	}
	g_object_unref (info);

	filename = g_strdup_printf ("%s%s",
				    base_name,
				    extension);
	child = g_file_get_child (dir, filename);
	g_free (filename);

	copy = 1;
	while ((info = g_file_query_info (child, G_FILE_ATTRIBUTE_STANDARD_TYPE, 0, NULL, NULL)) != NULL) {
		g_object_unref (info);
		g_object_unref (child);

		filename = g_strdup_printf ("%s-%d%s",
					    base_name,
					    copy,
					    extension);
		child = g_file_get_child (dir, filename);
		g_free (filename);

		copy++;
	}

	res = g_file_get_uri (child);
	g_object_unref (child);
	g_object_unref (dir);

	return res;
}
