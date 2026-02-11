simd_watch(int sock, void *sap_data)
{
	GIOChannel *io;

	DBG("sock %d, sap_data %p ", sock, sap_data);

	io = g_io_channel_unix_new(sock);

	g_io_channel_set_close_on_unref(io, TRUE);
	g_io_channel_set_encoding(io, NULL, NULL);
	g_io_channel_set_buffered(io, FALSE);

	u8500.io = io;
	u8500.sap_data = sap_data;
	u8500.state = STE_DISABLED;

	g_io_add_watch_full(io, G_PRIORITY_DEFAULT,
			G_IO_IN | G_IO_ERR | G_IO_HUP | G_IO_NVAL,
			simd_data_cb, NULL, NULL);
}
