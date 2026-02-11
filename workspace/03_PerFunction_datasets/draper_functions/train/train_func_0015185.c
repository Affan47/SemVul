stash_group_save_to_file(StashGroup *group, const gchar *filename,
		GKeyFileFlags flags)
{
	GKeyFile *keyfile;
	gchar *data;
	gint ret;

	keyfile = g_key_file_new();

	if (flags)
		g_key_file_load_from_file(keyfile, filename, flags, NULL);

	stash_group_save_to_key_file(group, keyfile);
	data = g_key_file_to_data(keyfile, NULL, NULL);
	ret = utils_write_file(filename, data);
	g_free(data);
	g_key_file_free(keyfile);
	return ret;
}
