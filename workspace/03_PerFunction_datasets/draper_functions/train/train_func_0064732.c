rb_uri_get_filesystem_type (const char *uri, char **mount_point)
{
	GFile *file;
	GFile *extant;
	GFileInfo *info;
	char *fstype = NULL;
	GError *error = NULL;

	if (mount_point != NULL) {
		*mount_point = NULL;
	}


	if (g_str_has_prefix (uri, "xrb")) {
		return NULL;
	}


	file = g_file_new_for_uri (uri);

	extant = rb_file_find_extant_parent (file);
	if (extant == NULL) {
		rb_debug ("unable to get filesystem type for %s: none of the directory structure exists", uri);
		g_object_unref (file);
		return NULL;
	}

	if (mount_point != NULL) {
		char *extant_uri;
		extant_uri = g_file_get_uri (extant);
		*mount_point = rb_uri_get_mount_point (extant_uri);
		g_free (extant_uri);
	}

	info = g_file_query_filesystem_info (extant, G_FILE_ATTRIBUTE_FILESYSTEM_TYPE, NULL, &error);
	if (info != NULL) {
		fstype = g_file_info_get_attribute_as_string (info, G_FILE_ATTRIBUTE_FILESYSTEM_TYPE);
		g_object_unref (info);
	} else {
		rb_debug ("error querying filesystem info: %s", error->message);
	}
	g_clear_error (&error);
	g_object_unref (file);
	g_object_unref (extant);
	return fstype;
}
