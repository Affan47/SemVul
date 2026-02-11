ctcp_reply_dcc_reject(IRC_SERVER_REC *server, const char *data,
				  const char *nick, const char *addr,
				  DCC_REC *chat)
{
        DCC_REC *dcc;
	char *type, *args;

	type = g_strdup(data);
	args = strchr(type, ' ');
        if (args != NULL) *args++ = '\0'; else args = "";

	dcc = dcc_find_request(dcc_str2type(type), nick, args);
	if (dcc != NULL) dcc_close(dcc);

        g_free(type);
}
