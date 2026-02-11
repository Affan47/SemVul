sasl_ntlm_try_empty_password_sync (CamelSasl *sasl,
                                   GCancellable *cancellable,
                                   GError **error)
{
#ifndef G_OS_WIN32
	CamelStream *stream;
	CamelNetworkSettings *network_settings;
	CamelSettings *settings;
	CamelService *service;
	CamelSaslNTLM *ntlm = CAMEL_SASL_NTLM (sasl);
	CamelSaslNTLMPrivate *priv = ntlm->priv;
	const gchar *cp;
	gchar *user;
	gchar buf[1024];
	gsize s;
	gchar *command;
	gint ret;

	if (priv->tried_helper)
		return !!priv->helper_stream;

	priv->tried_helper = TRUE;

	if (access (NTLM_AUTH_HELPER, X_OK))
		return FALSE;

	service = camel_sasl_get_service (sasl);

	settings = camel_service_ref_settings (service);
	g_return_val_if_fail (CAMEL_IS_NETWORK_SETTINGS (settings), FALSE);

	network_settings = CAMEL_NETWORK_SETTINGS (settings);
	user = camel_network_settings_dup_user (network_settings);

	g_object_unref (settings);

	g_return_val_if_fail (user != NULL, FALSE);

	cp = strchr (user, '\\');
	if (cp != NULL) {
		command = g_strdup_printf (
			"%s --helper-protocol ntlmssp-client-1 "
			"--use-cached-creds --username '%s' "
			"--domain '%.*s'", NTLM_AUTH_HELPER,
			cp + 1, (gint)(cp - user), user);
	} else {
		command = g_strdup_printf (
			"%s --helper-protocol ntlmssp-client-1 "
			"--use-cached-creds --username '%s'",
			NTLM_AUTH_HELPER, user);
	}

	stream = camel_stream_process_new ();

	ret = camel_stream_process_connect (
		CAMEL_STREAM_PROCESS (stream), command, NULL, error);

	g_free (command);
	g_free (user);

	if (ret) {
		g_object_unref (stream);
		return FALSE;
	}

	if (camel_stream_write_string (stream, "YR\n", cancellable, error) < 0) {
		g_object_unref (stream);
		return FALSE;
	}

	s = camel_stream_read (stream, buf, sizeof (buf), cancellable, NULL);
	if (s < 4) {
		g_object_unref (stream);
		return FALSE;
	}

	if (buf[0] != 'Y' || buf[1] != 'R' || buf[2] != ' ' || buf[s - 1] != '\n') {
		g_object_unref (stream);
		return FALSE;
	}

	buf[s - 1] = 0;

	priv->helper_stream = stream;
	priv->type1_msg = g_strdup (buf + 3);
	return TRUE;
#else

	return FALSE;
#endif
}
