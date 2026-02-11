ask_authorization_dialog_redirected_cb (OAuthAskAuthorizationDialog *dialog,
					gpointer                     user_data)
{
	FacebookService *self = user_data;
	const char      *uri;

	uri = oauth_ask_authorization_dialog_get_uri (dialog);
	if (g_str_has_prefix (uri, FACEBOOK_REDIRECT_URI)) {
		const char *uri_data;
		GHashTable *data;
		const char *access_token;
		const char *state;

		uri_data = uri + strlen (FACEBOOK_REDIRECT_URI "#");

		data = soup_form_decode (uri_data);
		access_token = NULL;
		state = g_hash_table_lookup (data, "state");
		if (g_strcmp0 (state, self->priv->state) == 0) {
			access_token = g_hash_table_lookup (data, "access_token");
			_facebook_service_set_access_token (self, access_token);
		}

		gtk_dialog_response (GTK_DIALOG (dialog),
				     (access_token != NULL) ? GTK_RESPONSE_OK : GTK_RESPONSE_CANCEL);

		g_hash_table_destroy (data);
	}
}
