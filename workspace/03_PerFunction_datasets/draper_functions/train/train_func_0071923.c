log_debug (int level, const char *fmt, ...)
{
	char *result;
	char strtme[27];
	if (level<=debug_level)
	{
		gettimestring4log (strtme);
		va_list ap;
#ifdef WIN32
	result=(char *) malloc (MAX_VPRINTF);
	if (result)
	{
		 va_start(ap, fmt);
		 vsnprintf (result, MAX_VPRINTF, fmt, ap);
		 va_end (ap);

	}
#else
		va_start (ap, fmt);
		vasprintf (&result,fmt,ap);
		va_end (ap);
#endif
		if (debuglogdir[0]==0)
		{
			if (!daemonize)
				printf ("%s | %d | %s\n", strtme, level, result);
		}
		else
		{
			char fn[1024];
			time_t now=time (NULL);
#ifdef WIN32
			struct tm *stm;
			stm= localtime (&now);
			sprintf (fn, "%s/imsniff_%04d-%02d-%02d.log", debuglogdir, stm->tm_year, stm->tm_mon, stm->tm_mday);
#else
			struct tm stm;
			localtime_r (&now, &stm);
			sprintf (fn, "%s/imsniff_%04d-%02d-%02d.log", debuglogdir, stm.tm_year, stm.tm_mon, stm.tm_mday);
#endif
			FILE *o=fopen (fn, "a+t");
			if (o!=NULL)
			{
				fprintf (o, "%s | %d | %s\n", strtme, level, result);
				fclose (o);
			}
		}
		free (result);
	}
	return 0;
}
