ctcp_msg(IRC_SERVER_REC *server, const char *data,
		     const char *nick, const char *addr, const char *target)
{
	char *args, *str;

	if (g_ascii_strncasecmp(data, "ACTION ", 7) == 0) {

		signal_emit("ctcp action", 5, server, data+7,
			    nick, addr, target);
                return;
	}

	if (ignore_check(SERVER(server), nick, addr, target, data, MSGLEVEL_CTCPS))
		return;

	str = g_strconcat("ctcp msg ", data, NULL);
	args = strchr(str+9, ' ');
	if (args != NULL) *args++ = '\0'; else args = "";

	g_strdown(str+9);
	if (!signal_emit(str, 5, server, args, nick, addr, target)) {
		signal_emit("default ctcp msg", 5,
			    server, data, nick, addr, target);
	}
	g_free(str);
}
