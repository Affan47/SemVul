ews_send_to_sync (CamelTransport *transport,
                  CamelMimeMessage *message,
                  CamelAddress *from,
                  CamelAddress *recipients,
                  GCancellable *cancellable,
                  GError **error)
{
	CamelNetworkSettings *network_settings;
	CamelEwsSettings *ews_settings;
	CamelInternetAddress *used_from;
	CamelSettings *settings;
	CamelService *service;
	EEwsConnection *cnc;
	gchar *ews_email;
	gchar *host_url;
	gchar *user;
	gboolean success = FALSE;

	service = CAMEL_SERVICE (transport);

	settings = camel_service_ref_settings (service);

	ews_settings = CAMEL_EWS_SETTINGS (settings);
	ews_email = camel_ews_settings_dup_email (ews_settings);
	host_url = camel_ews_settings_dup_hosturl (ews_settings);

	network_settings = CAMEL_NETWORK_SETTINGS (settings);
	user = camel_network_settings_dup_user (network_settings);

	g_object_unref (settings);

	used_from = camel_mime_message_get_from (message);

	if (!used_from && CAMEL_IS_INTERNET_ADDRESS (from))
		used_from = CAMEL_INTERNET_ADDRESS (from);

	if (!used_from || camel_address_length (CAMEL_ADDRESS (used_from)) == 0) {
		g_set_error_literal (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("Cannot send message with no From address"));
		goto exit;

	} else if (camel_address_length (CAMEL_ADDRESS (used_from)) > 1) {
		g_set_error_literal (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("Exchange server cannot send message with "
			"multiple From addresses"));
		goto exit;

	} else {
		const gchar *used_email = NULL;
		gboolean addresses_match;

		if (!camel_internet_address_get (used_from, 0, NULL, &used_email)) {
			g_set_error_literal (
				error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
				_("Failed to read From address"));
			goto exit;
		}

		addresses_match =
			(ews_email != NULL) &&
			(used_email != NULL) &&
			(g_ascii_strcasecmp (ews_email, used_email) == 0);

		if (!addresses_match) {
			g_set_error (
				error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
				_("Exchange server cannot send message as "
				"'%s', when the account was configured for "
				"address '%s'"),
				used_email ? used_email : "NULL",
				ews_email ? ews_email : "NULL");
			goto exit;
		}
	}

	cnc = e_ews_connection_find (host_url, user);
	if (!cnc) {
		g_set_error (
			error, CAMEL_SERVICE_ERROR,
			CAMEL_SERVICE_ERROR_NOT_CONNECTED,
			_("Service not connected"));
		goto exit;
	}

	success = camel_ews_utils_create_mime_message (
		cnc, "SendOnly", NULL, message, NULL,
		from, recipients, NULL, NULL, cancellable, error);

	g_object_unref (cnc);

exit:
	g_free (ews_email);
	g_free (host_url);
	g_free (user);

	return success;
}
