_uri_handle_file (GFile *dir, GFileInfo *fileinfo, GHashTable *handled, RBUriRecurseFunc func, gpointer user_data, GFile **descend)
{
	const char *file_id;
	gboolean is_dir;
	gboolean ret;
	GFileType file_type;
	GFile *child;

	*descend = NULL;
	if (_should_process (fileinfo) == FALSE) {
		rb_debug ("ignoring %s", g_file_info_get_name (fileinfo));
		return TRUE;
	}


	file_id = g_file_info_get_attribute_string (fileinfo, G_FILE_ATTRIBUTE_ID_FILE);
	if (file_id == NULL) {

	} else if (g_hash_table_lookup (handled, file_id) != NULL) {
		return TRUE;
	} else {
		g_hash_table_insert (handled, g_strdup (file_id), GINT_TO_POINTER (1));
	}


	file_type = g_file_info_get_attribute_uint32 (fileinfo, G_FILE_ATTRIBUTE_STANDARD_TYPE);
	switch (file_type) {
	case G_FILE_TYPE_DIRECTORY:
	case G_FILE_TYPE_MOUNTABLE:
		is_dir = TRUE;
		break;
	default:
		is_dir = FALSE;
		break;
	}

	child = g_file_get_child (dir, g_file_info_get_name (fileinfo));
	ret = (func) (child, is_dir, user_data);
	if (is_dir && ret) {
		*descend = child;
	} else {
		g_object_unref (child);
	}
	return ret;
}
