nautilus_directory_get_file_uri (NautilusDirectory *directory,
				 const char *file_name)
{
	GFile *child;
	char *result;

	g_return_val_if_fail (NAUTILUS_IS_DIRECTORY (directory), NULL);
	g_return_val_if_fail (file_name != NULL, NULL);

	result = NULL;

	child = g_file_get_child (directory->details->location, file_name);
	result = g_file_get_uri (child);
	g_object_unref (child);

	return result;
}
