hub_log_initialize(const char* file, int syslog)
{

	setlocale(LC_ALL, "C");

#ifdef MEMORY_DEBUG
	memfile = fopen(MEMORY_DEBUG_FILE, "w");
	if (!memfile)
	{
		fprintf(stderr, "Unable to create " MEMORY_DEBUG_FILE " for logging memory allocations\n");
		return;
	}
#endif

#ifdef NETWORK_DUMP_DEBUG
	netdump = fopen(NETWORK_DUMP_FILE, "w");
	if (!netdump)
	{
		fprintf(stderr, "Unable to create " NETWORK_DUMP_FILE " for logging network traffic\n");
		return;
	}
#endif

#ifndef WIN32
	if (syslog)
	{
		use_syslog = 1;
                #ifndef SYSTEMD
		openlog("uhub", LOG_PID, LOG_USER);
                #endif
	}
#endif


	if (!file)
	{
		logfile = stderr;
		return;
	}

	logfile = fopen(file, "a");
	if (!logfile)
	{
		logfile = stderr;
		return;
	}

}
