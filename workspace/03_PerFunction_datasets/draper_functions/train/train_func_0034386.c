mock_interaction_ask_password (GTlsInteraction *interaction,
                               GTlsPassword *password,
                               GCancellable *cancellable,
                               GError **error)
{
	MockInteraction *self = MOCK_INTERACTION (interaction);

	if (self->password) {
		g_tls_password_set_value (password, (const guchar *)self->password, -1);
		return G_TLS_INTERACTION_HANDLED;
	} else {
		return G_TLS_INTERACTION_UNHANDLED;
	}
}
