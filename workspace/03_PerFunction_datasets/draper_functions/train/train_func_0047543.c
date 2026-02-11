load_data_new (GthSourceTree *source_tree,
	       GFile         *file)
{
	LoadData *load_data;

	load_data = g_new0 (LoadData, 1);
	load_data->source_tree = source_tree;
	load_data->file_source = gth_main_get_file_source (file);
	load_data->folder = g_file_dup (file);

	return load_data;
}
