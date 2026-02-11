o_Wallops(char *format, ...)

{
	va_list args;
	char buffer[MAXLINE * 2];

	if (!DoWallops)
		return;

	va_start(args, format);
	vsprintf_irc(buffer, format, args);
	va_end(args);

#ifdef OPERWALL

	toserv(":%s OPERWALL :%s: %s\r\n", Me.name, n_OperServ, buffer);
#else

	toserv(":%s WALLOPS :%s: %s\r\n", Me.name, n_OperServ, buffer);
#endif

}
