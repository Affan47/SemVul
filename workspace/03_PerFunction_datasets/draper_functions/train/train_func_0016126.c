fr_channel_data_flush (FrChannelData *channel)
{
	GIOStatus status;

	while (((status = fr_channel_data_read (channel)) != G_IO_STATUS_ERROR) && (status != G_IO_STATUS_EOF))
		;
	fr_channel_data_close_source (channel);

	return status;
}
