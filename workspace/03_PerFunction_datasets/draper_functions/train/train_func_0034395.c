input_conn_free(struct input_conn *iconn)
{
	if (iconn->pending_connect)
		dbus_message_unref(iconn->pending_connect);

	if (iconn->ctrl_watch)
		g_source_remove(iconn->ctrl_watch);

	if (iconn->intr_watch)
		g_source_remove(iconn->intr_watch);

	if (iconn->sec_watch)
		g_source_remove(iconn->sec_watch);

	if (iconn->intr_io)
		g_io_channel_unref(iconn->intr_io);

	if (iconn->ctrl_io)
		g_io_channel_unref(iconn->ctrl_io);

	g_free(iconn->uuid);
	g_free(iconn->fake);
	g_free(iconn);
}
