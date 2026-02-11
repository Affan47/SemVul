g_at_io_write(GAtIO *io, const gchar *data, gsize count)
{
	GIOStatus status;
	gsize bytes_written;

	status = g_io_channel_write_chars(io->channel, data,
						count, &bytes_written, NULL);

	if (status != G_IO_STATUS_NORMAL) {
		g_source_remove(io->read_watch);
		return 0;
	}

	g_at_util_debug_chat(FALSE, data, bytes_written,
				io->debugf, io->debug_data);

	return bytes_written;
}
