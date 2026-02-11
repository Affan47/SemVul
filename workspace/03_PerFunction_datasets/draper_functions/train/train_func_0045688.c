nautilus_directory_get_for_file (NautilusFile *file)
{
	char *uri;
	NautilusDirectory *directory;

	g_return_val_if_fail (NAUTILUS_IS_FILE (file), NULL);

	uri = nautilus_file_get_uri (file);
	directory = nautilus_directory_get_by_uri (uri);
	g_free (uri);
	return directory;
}
