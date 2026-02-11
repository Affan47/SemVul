smtp_transport_connect_sync (CamelService *service,
                             GCancellable *cancellable,
                             GError **error)
{
	CamelSmtpTransport *transport = CAMEL_SMTP_TRANSPORT (service);
	CamelNetworkSettings *network_settings;
	CamelSettings *settings;
	gchar *host;
	gchar *mechanism;
	gboolean auth_required;
	gboolean success = TRUE;

	settings = camel_service_ref_settings (service);

	network_settings = CAMEL_NETWORK_SETTINGS (settings);
	host = camel_network_settings_dup_host (network_settings);
	mechanism = camel_network_settings_dup_auth_mechanism (network_settings);

	g_object_unref (settings);


	if (g_strcmp0 (mechanism, "POPB4SMTP") == 0) {
		GByteArray *chal;
		CamelSasl *sasl;

		sasl = camel_sasl_new ("smtp", "POPB4SMTP", service);
		chal = camel_sasl_challenge_sync (sasl, NULL, cancellable, error);
		if (chal != NULL)
			g_byte_array_free (chal, TRUE);

		if (camel_sasl_get_authenticated (sasl))
			success = connect_to_server (
				service, cancellable, error);
		else
			success = FALSE;

		g_object_unref (sasl);

		goto exit;
	}

	success = connect_to_server (service, cancellable, error);

	if (!success)
		return FALSE;


	auth_required =
		(mechanism != NULL) &&
		(transport->authtypes != NULL) &&
		(g_hash_table_size (transport->authtypes) > 0) &&
		(transport->flags & CAMEL_SMTP_TRANSPORT_IS_ESMTP);

	if (auth_required) {
		CamelSession *session;

		session = camel_service_ref_session (service);

		if (g_hash_table_lookup (transport->authtypes, mechanism)) {
			success = camel_session_authenticate_sync (
				session, service, mechanism,
				cancellable, error);
		} else {
			g_set_error (
				error, CAMEL_SERVICE_ERROR,
				CAMEL_SERVICE_ERROR_CANT_AUTHENTICATE,
				_("SMTP server %s does not support %s "
				"authentication"), host, mechanism);
			success = FALSE;
		}

		g_object_unref (session);

		if (!success)
			transport->connected = FALSE;
	}

exit:
	g_free (host);
	g_free (mechanism);

	return success;
}
