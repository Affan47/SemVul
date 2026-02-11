g_io_gnutls_read(GIOChannel *channel, gchar *buf,
				gsize count, gsize *bytes_read, GError **err)
{
	GIOGnuTLSChannel *gnutls_channel = (GIOGnuTLSChannel *) channel;
	GIOStatus status;
	ssize_t result;

	DBG("channel %p count %zu", channel, count);

	*bytes_read = 0;

again:
	status = check_handshake(channel, err);
	if (status != G_IO_STATUS_NORMAL)
		return status;

	result = gnutls_record_recv(gnutls_channel->session, buf, count);

	DBG("result %zd", result);

	if (result == GNUTLS_E_REHANDSHAKE) {
		gnutls_channel->established = FALSE;
		goto again;
	}

	if (result == GNUTLS_E_INTERRUPTED || result == GNUTLS_E_AGAIN) {
		GIOFlags flags = g_io_channel_get_flags(channel);

		if (gnutls_channel->again == TRUE)
			return G_IO_STATUS_AGAIN;

		if (flags & G_IO_FLAG_NONBLOCK)
			return G_IO_STATUS_AGAIN;

		goto again;
	}

	if (result == GNUTLS_E_UNEXPECTED_PACKET_LENGTH)
		return G_IO_STATUS_EOF;

	if (result < 0) {
		g_set_error(err, G_IO_CHANNEL_ERROR,
				G_IO_CHANNEL_ERROR_FAILED, "Stream corrupted");
		return G_IO_STATUS_ERROR;
	}

	*bytes_read = result;

	return (result > 0) ? G_IO_STATUS_NORMAL : G_IO_STATUS_EOF;
}
