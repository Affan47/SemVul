sap_connect_cb(GIOChannel *io, GError *gerr, gpointer data)
{
	struct sap_connection *conn = data;

	DBG("conn %p, io %p", conn, io);

	if (!conn)
		return;


	start_guard_timer(conn, SAP_TIMER_NO_ACTIVITY);

	g_io_add_watch_full(io, G_PRIORITY_DEFAULT,
			G_IO_IN | G_IO_ERR | G_IO_HUP | G_IO_NVAL,
			sap_io_cb, conn, sap_io_destroy);
}
