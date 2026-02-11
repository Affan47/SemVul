ctcp_msg(IRC_SERVER_REC *server, const char *data,
		     const char *nick, const char *addr, const char *target)
{
	if (g_ascii_strncasecmp(data, "dcc ", 4) != 0)
                return;
	data += 4;

	signal_emit("ctcp msg dcc", 5, server, data, nick, addr, target);
        signal_stop();
}
