fi_gui_file_get_progress(const struct fileinfo_data *file)
{
	g_return_val_if_fail(file, 0);
	return file->progress / 100;
}
