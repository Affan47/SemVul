g_load_file_async (GFile               *file,
		   int                  io_priority,
		   GCancellable        *cancellable,
		   BufferReadyCallback  callback,
		   gpointer             user_data)
{
	LoadData *load_data;

	load_data = g_new0 (LoadData, 1);
	load_data->io_priority = io_priority;
	load_data->cancellable = cancellable;
	load_data->callback = callback;
	load_data->user_data = user_data;

	g_file_read_async (file, io_priority, cancellable, load_file__file_read_cb, load_data);
}
