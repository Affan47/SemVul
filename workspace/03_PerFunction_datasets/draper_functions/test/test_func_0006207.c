smtp_rset (CamelSmtpTransport *transport,
           GCancellable *cancellable,
           GError **error)
{

	gchar *cmdbuf, *respbuf = NULL;

	cmdbuf = g_strdup ("RSET\r\n");

	d (fprintf (stderr, "sending : %s", cmdbuf));

	if (camel_stream_write_string (
		transport->ostream, cmdbuf, cancellable, error) == -1) {
		g_free (cmdbuf);
		g_prefix_error (error, _("RSET command failed: "));
		camel_service_disconnect_sync (
			CAMEL_SERVICE (transport),
			FALSE, cancellable, NULL);
		return FALSE;
	}
	g_free (cmdbuf);

	do {

		g_free (respbuf);
		respbuf = camel_stream_buffer_read_line (
			CAMEL_STREAM_BUFFER (transport->istream),
			cancellable, error);
		if (respbuf == NULL) {
			g_prefix_error (error, _("RSET command failed: "));
			camel_service_disconnect_sync (
				CAMEL_SERVICE (transport),
				FALSE, cancellable, NULL);
			return FALSE;
		}
		if (strncmp (respbuf, "250", 3) != 0) {
			smtp_set_error (
				transport, respbuf, cancellable, error);
			g_prefix_error (error, _("RSET command failed: "));
			g_free (respbuf);
			return FALSE;
		}
	} while (*(respbuf+3) == '-');
	g_free (respbuf);

	return TRUE;
}
