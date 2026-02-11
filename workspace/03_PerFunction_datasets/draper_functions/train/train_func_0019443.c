whois_list_send(IRC_SERVER_REC *server, GSList *nicks)
{
	GSList *tmp;
	GString *str;
	char *nick;
        int count;

	str = g_string_new(NULL);
	count = 0;

	for (tmp = nicks; tmp != NULL; tmp = tmp->next) {
		nick = tmp->data;

		count++;
		g_string_append_printf(str, "%s,", nick);

		if (count >= server->max_whois_in_cmd) {
			g_string_truncate(str, str->len-1);
			whois_send(server, str->str, str->str);
			g_string_truncate(str, 0);
                        count = 0;
		}
	}

	if (str->len > 0) {
		g_string_truncate(str, str->len-1);
		whois_send(server, str->str, str->str);
	}

	g_string_free(str, TRUE);
}
