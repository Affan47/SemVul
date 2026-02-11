sasl_plain_challenge_sync (CamelSasl *sasl,
                           GByteArray *token,
                           GCancellable *cancellable,
                           GError **error)
{
	CamelNetworkSettings *network_settings;
	CamelSettings *settings;
	CamelService *service;
	GByteArray *buf = NULL;
	const gchar *password;
	gchar *user;

	service = camel_sasl_get_service (sasl);

	settings = camel_service_ref_settings (service);
	g_return_val_if_fail (CAMEL_IS_NETWORK_SETTINGS (settings), NULL);

	network_settings = CAMEL_NETWORK_SETTINGS (settings);
	user = camel_network_settings_dup_user (network_settings);

	g_object_unref (settings);

	g_return_val_if_fail (user != NULL, NULL);

	password = camel_service_get_password (service);
	g_return_val_if_fail (password != NULL, NULL);


	buf = g_byte_array_new ();
	g_byte_array_append (buf, (guint8 *) "", 1);
	g_byte_array_append (buf, (guint8 *) user, strlen (user));
	g_byte_array_append (buf, (guint8 *) "", 1);
	g_byte_array_append (buf, (guint8 *) password, strlen (password));

	camel_sasl_set_authenticated (sasl, TRUE);

	g_free (user);

	return buf;
}
