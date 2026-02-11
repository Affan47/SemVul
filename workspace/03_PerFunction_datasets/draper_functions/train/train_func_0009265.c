imapx_parse_uids (CamelIMAPXStream *is,
                  GCancellable *cancellable,
                  GError **error)
{
	GPtrArray *uids;
	guchar *token;
	gchar **splits;
	guint len, str_len;
	gint tok, i;

	tok = camel_imapx_stream_token (is, &token, &len, cancellable, error);
	if (tok < 0)
		return NULL;

	uids = g_ptr_array_new ();
	splits = g_strsplit ((gchar *) token, ",", -1);
	str_len = g_strv_length (splits);

	for (i = 0; i < str_len; i++)	{
		if (g_strstr_len (splits[i], -1, ":")) {
			gchar **seq = g_strsplit (splits[i], ":", -1);
			guint32 uid1 = strtoul ((gchar *) seq[0], NULL, 10);
			guint32 uid2 = strtoul ((gchar *) seq[1], NULL, 10);

			generate_uids_from_sequence (uids, uid1, uid2);
			g_strfreev (seq);
		} else {
			guint32 uid = strtoul ((gchar *) splits[i], NULL, 10);
			g_ptr_array_add (uids, GUINT_TO_POINTER (uid));
		}
	}

	g_strfreev (splits);

	return uids;
}
