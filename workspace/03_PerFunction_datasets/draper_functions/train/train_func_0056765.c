io_data_unref(struct io_data *data)
{
	data->ref--;

	if (data->ref)
		return;

	if (data->io)
		g_io_channel_unref(data->io);

	g_free(data);
}
