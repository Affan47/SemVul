sig_message_public(SERVER_REC *server, const char *msg,
			       const char *nick, const char *address,
			       const char *target)
{
	if (ignore_check(server, nick, address, target, msg, MSGLEVEL_PUBLIC))
		signal_stop();
}
