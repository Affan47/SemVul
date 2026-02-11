daap_receive_header (GIOChannel *sock_chan, gchar **header)
{
	guint n_total_bytes_recvd = 0;
	gsize linelen;
	gchar *response, *recv_line;
	GIOStatus io_stat;
	GError *err = NULL;

	if (NULL != header) {
		*header = NULL;
	}

	response = g_malloc0 (MAX_HEADER_LENGTH);
	if (NULL == response) {
		XMMS_DBG ("Error: couldn't allocate memory for response.\n");
		return;
	}


	do {
		io_stat = g_io_channel_read_line (sock_chan, &recv_line, &linelen,
		                                  NULL, &err);
		if (io_stat == G_IO_STATUS_ERROR) {
			XMMS_DBG ("Error reading from channel: %s\n", err->message);
			break;
		}

		if (NULL != recv_line) {
			memcpy (response+n_total_bytes_recvd, recv_line, linelen);
			n_total_bytes_recvd += linelen;

			if (strcmp (recv_line, "\r\n") == 0) {
				g_free (recv_line);
				if (NULL != header) {
					*header = g_malloc0 (n_total_bytes_recvd);
					if (NULL == *header) {
						XMMS_DBG ("error: couldn't allocate header\n");
						break;
					}
					memcpy (*header, response, n_total_bytes_recvd);
				}
				break;
			}

			g_free (recv_line);
		}

		if (io_stat == G_IO_STATUS_EOF) {
			break;
		}

		if (n_total_bytes_recvd >= MAX_HEADER_LENGTH) {
			XMMS_DBG ("Warning: Maximum header size reached without finding "
			          "end of header; bailing.\n");
			break;
		}
	} while (TRUE);

	g_free (response);

	if (sock_chan) {
		g_io_channel_flush (sock_chan, &err);
		if (NULL != err) {
			XMMS_DBG ("Error flushing buffer: %s\n", err->message);
			return;
		}
	}
}
