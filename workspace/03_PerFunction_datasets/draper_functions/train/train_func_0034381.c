ctrl_watch_cb(GIOChannel *chan, GIOCondition cond, gpointer data)
{
	struct input_conn *iconn = data;
	char address[18];

	ba2str(&iconn->idev->dst, address);

	DBG("Device %s disconnected", address);


	if ((cond & (G_IO_HUP | G_IO_ERR)) && iconn->intr_watch)
		g_io_channel_shutdown(chan, TRUE, NULL);

	iconn->ctrl_watch = 0;

	g_io_channel_unref(iconn->ctrl_io);
	iconn->ctrl_io = NULL;


	if (iconn->intr_io && !(cond & G_IO_NVAL))
		g_io_channel_shutdown(iconn->intr_io, TRUE, NULL);

	return FALSE;
}
