send_and_handle_redirection (ECalBackendCalDAV *cbdav,
                             SoupMessage *msg,
                             gchar **new_location,
                             GCancellable *cancellable,
                             GError **error)
{
	gchar *old_uri = NULL;

	g_return_if_fail (E_IS_CAL_BACKEND_CALDAV (cbdav));
	g_return_if_fail (msg != NULL);

	if (new_location)
		old_uri = soup_uri_to_string (soup_message_get_uri (msg), FALSE);

	soup_message_set_flags (msg, SOUP_MESSAGE_NO_REDIRECT);
	soup_message_add_header_handler (msg, "got_body", "Location", G_CALLBACK (redirect_handler), cbdav->priv->session);
	soup_message_headers_append (msg->request_headers, "Connection", "close");
	soup_session_send_message (cbdav->priv->session, msg);

	if (msg->status_code == SOUP_STATUS_SSL_FAILED) {
		ESource *source;
		ESourceWebdav *extension;
		ESourceRegistry *registry;
		EBackend *backend;
		ETrustPromptResponse response;
		ENamedParameters *parameters;

		backend = E_BACKEND (cbdav);
		source = e_backend_get_source (backend);
		registry = e_cal_backend_get_registry (E_CAL_BACKEND (backend));
		extension = e_source_get_extension (source, E_SOURCE_EXTENSION_WEBDAV_BACKEND);

		parameters = e_named_parameters_new ();

		response = e_source_webdav_prepare_ssl_trust_prompt (extension, msg, registry, parameters);
		if (response == E_TRUST_PROMPT_RESPONSE_UNKNOWN) {
			response = e_backend_trust_prompt_sync (backend, parameters, cancellable, error);
			if (response != E_TRUST_PROMPT_RESPONSE_UNKNOWN)
				e_source_webdav_store_ssl_trust_prompt (extension, msg, response);
		}

		e_named_parameters_free (parameters);

		if (response == E_TRUST_PROMPT_RESPONSE_ACCEPT ||
		    response == E_TRUST_PROMPT_RESPONSE_ACCEPT_TEMPORARILY) {
			g_object_set (cbdav->priv->session, SOUP_SESSION_SSL_STRICT, FALSE, NULL);
			soup_session_send_message (cbdav->priv->session, msg);
		}
	}

	if (new_location) {
		gchar *new_loc = soup_uri_to_string (soup_message_get_uri (msg), FALSE);

		if (new_loc && old_uri && !g_str_equal (new_loc, old_uri))
			*new_location = new_loc;
		else
			g_free (new_loc);
	}

	g_free (old_uri);
}
