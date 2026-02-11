log_message(const char *fmt, ...)
{
	va_list ap;


	char    buf[1024];
	int     len;
	char   *msg;


	snprintf(buf + 4, sizeof(buf) - 4, "&LOG %s ", global.serverName);
	len = strlen(buf + 4);
	msg = buf + len + 4;
	va_start(ap, fmt);
	vsnprintf(buf + 4 + len, sizeof(buf) - 4 - len, fmt, ap);
	va_end(ap);
#if LOG_CHANNEL

	if(!Logging)
	{
		len += strlen(buf + 4 + len);
		set_tag(buf, MSG_SERVER_PUBLIC);
		set_len(buf, len);

		Logging = 1;
		(void) send_to_channel("&LOG", buf, len + 4);
		Logging = 0;
	}


#endif

	if(option(ON_LOG_STDOUT) || (global.logLevel == 2047) )
	{
		char timebuf[64];
		time_t curtime;
		struct tm *loctime;
		curtime = time(NULL);
		loctime = localtime(&curtime);
		strftime(timebuf, 64, "%b %d %H:%M:%S ", loctime);
		fputs(timebuf , stdout);
		fputs(msg, stdout);
		fputc('\n', stdout);
		fflush(stdout);
	}
}
