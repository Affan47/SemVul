share_settings_set_name_from_folder (const gchar *path)
{
	gchar *name;

	g_return_if_fail (path != NULL);

	if (strcmp (path, "/") == 0)
		name = g_strdup (_("File System"));
	else
		name = g_path_get_basename (path);

	set_smb_name (name);
	g_free (name);
}
