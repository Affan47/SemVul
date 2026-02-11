hs_notice(char *Serv, char *nick, int sockfd, char
                      *format, ...)
{
	va_list args;
	char finstr[MAXLINE * 2];
	struct NickInfo *nptr;

	va_start(args, format);
	vsprintf_irc(finstr, format, args);
	va_end(args);

	if (sockfd == NODCC)
	{
		if (nick)
		{
			nptr = GetLink(nick);
			if (nptr && (nptr->flags & NS_PRIVMSG))
				toserv(":%s PRIVMSG %s :%s\r\n",
				       Serv, nick, finstr);
			else
				toserv(":%s NOTICE %s :%s\r\n",
				       Serv, nick, finstr);
		}
	}
	else
	{
		writesocket(sockfd, finstr);
		writesocket(sockfd, "\r\n");
	}
}
