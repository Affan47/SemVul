click_pkid_data_is_click (const gchar *data)
{
	gchar **tokens;
	gboolean ret;

	tokens = g_strsplit (data, ",", 2);
	ret = g_strcmp0 (tokens[0], "local:click") == 0 ||
	      g_strcmp0 (tokens[0], "installed:click") == 0;
	g_strfreev (tokens);

	return ret;
}
