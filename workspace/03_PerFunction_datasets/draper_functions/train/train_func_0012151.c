collect_directories_by_container (gpointer key, gpointer value, gpointer callback_data)
{
	NemoDirectory *directory;
	CollectData *collect_data;
	GFile *location;

	location = (GFile *) key;
	directory = NEMO_DIRECTORY (value);
	collect_data = (CollectData *) callback_data;

	if (g_file_has_prefix (location, collect_data->container) ||
	    g_file_equal (collect_data->container, location)) {
		nemo_directory_ref (directory);
		collect_data->directories =
			g_list_prepend (collect_data->directories,
					directory);
	}
}
