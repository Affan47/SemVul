clog_msg_send_syslog()
{
const char *p=logbuf;
int	loglevel=LOG_INFO;

	if (*p == 'E')	loglevel=LOG_ERR;
	while (*p && *p != ':')
		p++;
	if (*p)	p++;
	while (*p == ' ')	++p;

	syslog(loglevel, "%s", p);
}
