message_set_logfile (const char* filename)
{
	if (g_logfile) {
		fclose (g_logfile);
		g_logfile = NULL;
	}

	if (filename)
		g_logfile = fopen (filename, "w");

	if (g_logfile) {
		g_lastchar = '\n';
#ifdef _WIN32
		g_timestamp = GetTickCount ();
#else
		gettimeofday (&g_timestamp, NULL);
#endif
		dc_datetime_t dt = {0};
		dc_ticks_t now = dc_datetime_now ();
		dc_datetime_gmtime (&dt, now);
		message ("DATETIME %u-%02u-%02uT%02u:%02u:%02uZ (%lu)\n",
			dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second,
			(unsigned long) now);
		message ("VERSION %s\n", dc_version (NULL));
	}
}
