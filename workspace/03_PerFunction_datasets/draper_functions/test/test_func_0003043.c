delete_contact (EBookBackendWebdav *webdav,
                const gchar *uri,
                GCancellable *cancellable)
{
	SoupMessage *message;
	guint        status;

	message = soup_message_new (SOUP_METHOD_DELETE, uri);
	soup_message_headers_append (message->request_headers, "User-Agent", USERAGENT);
	soup_message_headers_append (message->request_headers, "Connection", "close");

	status = send_and_handle_ssl (webdav, message, cancellable);
	g_object_unref (message);

	return status;
}
