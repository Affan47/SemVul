_g_file_check_permissions (GFile *file,
			   int    mode)
{
	gboolean   result = TRUE;
	GFileInfo *info;
	GError    *err = NULL;
	gboolean   default_permission_when_unknown = TRUE;

	info = g_file_query_info (file, "access::*", 0, NULL, &err);
	if (err != NULL) {
		g_clear_error (&err);
		result = FALSE;
	}
	else {
		if ((mode & R_OK) == R_OK) {
			if (g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_ACCESS_CAN_READ))
				result = (result && g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_READ));
			else
				result = (result && default_permission_when_unknown);
		}

		if ((mode & W_OK) == W_OK) {
			if (g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE))
				result = (result && g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_WRITE));
			else
				result = (result && default_permission_when_unknown);
		}

		if ((mode & X_OK) == X_OK) {
			if (g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE))
				result = (result && g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE));
			else
				result = (result && default_permission_when_unknown);
		}

		g_object_unref (info);
	}

	return result;
}
