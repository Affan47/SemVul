gth_file_source_vfs_to_gio_file (GthFileSource *file_source,
				 GFile         *file)
{
	char  *uri;
	GFile *gio_file;

	uri = g_file_get_uri (file);
	gio_file = g_file_new_for_uri (g_str_has_prefix (uri, "vfs+") ? uri + 4 : uri);
	g_free (uri);

	return gio_file;
}
