pk_transaction_process_script (PkTransaction *transaction, const gchar *filename)
{
	GFile *file = NULL;
	GFileInfo *info = NULL;
	guint file_uid;
	gchar *command = NULL;
	gint exit_status = 0;
	gboolean ret;
	GError *error = NULL;
	PkRoleEnum role;


	file = g_file_new_for_path (filename);
	info = g_file_query_info (file,
				  G_FILE_ATTRIBUTE_UNIX_UID ","
				  G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE,
				  G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, &error);
	if (info == NULL) {
		g_warning ("failed to get info: %s", error->message);
		goto out;
	}


	ret = g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE);
	if (!ret) {
		g_warning ("%s is not executable", filename);
		goto out;
	}


	file_uid = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_UID);
	if (file_uid != 0) {
		g_warning ("%s is not owned by the root user", filename);
		goto out;
	}


	role = pk_transaction_get_role (transaction);
	command = g_strdup_printf ("%s %s NOTAPISTABLE",
				   filename,
				   pk_role_enum_to_string (role));


	ret = g_spawn_command_line_sync (command, NULL, NULL, &exit_status, &error);
	if (!ret) {
		g_warning ("failed to spawn %s [%i]: %s", command, exit_status, error->message);
		g_error_free (error);
	} else {
		g_debug ("ran %s", command);
	}

out:
	g_free (command);
	if (info != NULL)
		g_object_unref (info);
	if (file != NULL)
		g_object_unref (file);
}
