dumpTimestamp(char *msg)
{
	char		buf[256];
	time_t		now = time(NULL);


	if (strftime(buf, sizeof(buf),
#ifndef WIN32
				 "%Y-%m-%d %H:%M:%S %Z",
#else
				 "%Y-%m-%d %H:%M:%S",
#endif
				 localtime(&now)) != 0)
		printf("-- %s %s\n\n", msg, buf);
}
