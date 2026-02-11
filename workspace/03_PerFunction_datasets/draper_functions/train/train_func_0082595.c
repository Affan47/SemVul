socks5_request_connect (CamelTcpStreamRaw *raw,
                        PRFileDesc *fd,
                        const gchar *host,
                        gint port,
                        GCancellable *cancellable,
                        GError **error)
{
	gchar *request;
	gchar reply[3];
	gint host_len;
	gint request_len;
	gint num_written;

	host_len = strlen (host);
	if (host_len > 255) {
		g_set_error (error, CAMEL_ERROR, CAMEL_ERROR_GENERIC, _("Hostname is too long (maximum is 255 characters)"));
		return FALSE;
	}

	request_len = 4 + 1 + host_len + 2;
	request = g_new (gchar, request_len);

	request[0] = 0x05;
	request[1] = 0x01;
	request[2] = 0x00;
	request[3] = 0x03;
	request[4] = host_len;
	memcpy (request + 5, host, host_len);
	request[5 + host_len] = (port & 0xff00) >> 8;
	request[5 + host_len + 1] = port & 0xff;

	d (g_print ("  writing SOCKS5 request for connection\n"));
	num_written = write_to_prfd (fd, request, request_len, cancellable, error);
	g_free (request);

	if (num_written != request_len) {
		d (g_print ("  failed: %d\n", errno));
		return FALSE;
	}

	d (g_print ("  reading SOCKS5 reply\n"));
	if (read_from_prfd (fd, reply, sizeof (reply), cancellable, error) != sizeof (reply)) {
		d (g_print ("  failed: %d\n", errno));
		return FALSE;
	}

	if (reply[0] != 0x05) {
		g_set_error (error, CAMEL_SERVICE_ERROR, CAMEL_SERVICE_ERROR_NOT_CONNECTED, _("Invalid reply from proxy server"));
		return FALSE;
	}

	if (reply[1] != 0x00) {
		g_set_error (error, CAMEL_SERVICE_ERROR, CAMEL_SERVICE_ERROR_NOT_CONNECTED, "%s", socks5_reply_error_to_string (reply[1]));
		return FALSE;
	}

	if (reply[2] != 0x00) {
		g_set_error (error, CAMEL_SERVICE_ERROR, CAMEL_SERVICE_ERROR_NOT_CONNECTED, _("Invalid reply from proxy server"));
		return FALSE;
	}


	if (!socks5_consume_reply_address (raw, fd, cancellable, error))
		return FALSE;

	return TRUE;
}
