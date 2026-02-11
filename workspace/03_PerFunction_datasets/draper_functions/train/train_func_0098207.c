download_contact (EBookBackendWebdav *webdav,
                  const gchar *uri,
                  GCancellable *cancellable)
{
	SoupMessage *message;
	const gchar  *etag;
	EContact    *contact;
	guint        status;

	message = soup_message_new (SOUP_METHOD_GET, uri);
	soup_message_headers_append (message->request_headers, "User-Agent", USERAGENT);
	soup_message_headers_append (message->request_headers, "Connection", "close");

	status = send_and_handle_ssl (webdav, message, cancellable);
	if (status != 200) {
		g_warning ("Couldn't load '%s' (http status %d)", uri, status);
		g_object_unref (message);
		return NULL;
	}

	if (message->response_body == NULL) {
		g_message ("no response body after requesting '%s'", uri);
		g_object_unref (message);
		return NULL;
	}

	if (message->response_body->length <= 11 || 0 != g_ascii_strncasecmp ((const gchar *) message->response_body->data, "BEGIN:VCARD", 11)) {
		g_object_unref (message);
		return NULL;
	}

	etag = soup_message_headers_get_list (message->response_headers, "ETag");


	contact = e_contact_new_from_vcard_with_uid (message->response_body->data, uri);
	if (contact == NULL) {
		g_warning ("Invalid vcard at '%s'", uri);
		g_object_unref (message);
		return NULL;
	}


	if (etag != NULL) {
		webdav_contact_set_etag (contact, etag);
	}

	g_object_unref (message);
	return contact;
}
