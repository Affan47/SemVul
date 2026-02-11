soup_message_set_https_status (SoupMessage *msg, SoupConnection *conn)
{
	SoupSocket *sock;

	sock = conn ? soup_connection_get_socket (conn) : NULL;
	if (sock && soup_socket_is_ssl (sock)) {
		GTlsCertificate *certificate;
		GTlsCertificateFlags errors;

		g_object_get (sock,
			      SOUP_SOCKET_TLS_CERTIFICATE, &certificate,
			      SOUP_SOCKET_TLS_ERRORS, &errors,
			      NULL);
		g_object_set (msg,
			      SOUP_MESSAGE_TLS_CERTIFICATE, certificate,
			      SOUP_MESSAGE_TLS_ERRORS, errors,
			      NULL);
		if (certificate)
			g_object_unref (certificate);
	} else {
		g_object_set (msg,
			      SOUP_MESSAGE_TLS_CERTIFICATE, NULL,
			      SOUP_MESSAGE_TLS_ERRORS, 0,
			      NULL);
	}
}
