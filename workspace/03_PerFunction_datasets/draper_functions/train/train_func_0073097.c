notice(char *from, char *nick, char *format, ...)
{
	char finalstr[MAXLINE * 2];
	struct NickInfo *nptr;
	va_list args;

	va_start(args, format);
	vsprintf_irc(finalstr, format, args);
	va_end(args);

	nptr = GetLink(nick);
	if (nptr && (nptr->flags & NS_PRIVMSG))
		toserv(":%s PRIVMSG %s :%s\r\n", from, nick, finalstr);
	else
	{
		toserv(":%s NOTICE %s :%s\r\n", ServerNotices ? Me.name : from, nick,
		       finalstr);
	}

}
