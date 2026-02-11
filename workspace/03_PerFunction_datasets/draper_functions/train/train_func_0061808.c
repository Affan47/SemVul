nautilus_directory_call_when_ready (NautilusDirectory *directory,
				    NautilusFileAttributes file_attributes,
				    gboolean wait_for_all_files,
				    NautilusDirectoryCallback callback,
				    gpointer callback_data)
{
	g_return_if_fail (NAUTILUS_IS_DIRECTORY (directory));
	g_return_if_fail (callback != NULL);

	NAUTILUS_DIRECTORY_CLASS (G_OBJECT_GET_CLASS (directory))->call_when_ready
		(directory, file_attributes, wait_for_all_files,
		 callback, callback_data);
}
