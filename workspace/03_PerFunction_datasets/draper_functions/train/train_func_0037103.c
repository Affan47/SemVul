gkrellm_client_send_to_server(gchar *key_name, gchar *line)
	{
	gchar		*str;
	gboolean	result;

	if (!key_name || !line || !*line)
		return FALSE;
	str = g_strdup_printf("<%s>\n", key_name);
	client_send_to_server(str);
	g_free(str);
	if (line[strlen(line) - 1] != '\n')
		{
		str = g_strdup_printf("%s\n", line);
		result = client_send_to_server(str);
		g_free(str);
		}
	else
		result = client_send_to_server(line);

	return result;
	}
