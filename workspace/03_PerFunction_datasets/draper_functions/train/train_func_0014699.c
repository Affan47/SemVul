facebook_utils_get_authorization_url (WebAuthorization  access_type,
				      const char       *state)
{
	GHashTable *data_set;
	GString    *link;
	GList      *keys;
	GList      *scan;

	data_set = g_hash_table_new (g_str_hash, g_str_equal);
	g_hash_table_insert (data_set, "client_id", GTHUMB_FACEBOOK_APP_ID);
	g_hash_table_insert (data_set, "redirect_uri", FACEBOOK_REDIRECT_URI);
	g_hash_table_insert (data_set, "scope", get_access_type_name (access_type));
	g_hash_table_insert (data_set, "response_type", "token");
	g_hash_table_insert (data_set, "state", (char *) state);

	link = g_string_new ("https://www.facebook.com/dialog/oauth?");
	keys = g_hash_table_get_keys (data_set);
	for (scan = keys; scan; scan = scan->next) {
		char *key = scan->data;
		char *encoded;

		if (scan != keys)
			g_string_append (link, "&");
		g_string_append (link, key);
		g_string_append (link, "=");
		encoded = soup_uri_encode (g_hash_table_lookup (data_set, key), NULL);
		g_string_append (link, encoded);

		g_free (encoded);
	}

	g_list_free (keys);
	g_hash_table_destroy (data_set);

	return g_string_free (link, FALSE);
}
