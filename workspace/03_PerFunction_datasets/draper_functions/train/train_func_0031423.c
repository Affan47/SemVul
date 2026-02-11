write_buffer_to_channel (GIOChannel *chan, gchar *buf, gint bufsize)
{
	guint total_sent_bytes = 0;
	gsize sent_bytes;
	GIOStatus io_stat;
	GError *err = NULL;

	do {
		io_stat = g_io_channel_write_chars (chan,
		                                    buf + total_sent_bytes,
		                                    bufsize - total_sent_bytes,
		                                    &sent_bytes,
		                                    &err);
		if (io_stat == G_IO_STATUS_ERROR) {
			if (NULL != err) {
				XMMS_DBG ("Error writing to channel: %s\n", err->message);
			}
			break;
		}

		bufsize -= sent_bytes;
		total_sent_bytes += sent_bytes;
	} while (bufsize > 0);

	g_io_channel_flush (chan, &err);
	if (NULL != err) {
		XMMS_DBG ("warning: error flushing channel: %s\n", err->message);
	}
}
