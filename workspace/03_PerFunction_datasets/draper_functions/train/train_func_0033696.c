sphLogEntry ( ESphLogLevel eLevel, char * sBuf )
{
#if USE_WINDOWS
	if ( g_bService && g_iLogFile==STDOUT_FILENO )
	{
		HANDLE hEventSource;
		LPCTSTR lpszStrings[2];

		hEventSource = RegisterEventSource ( NULL, g_sServiceName );
		if ( hEventSource )
		{
			lpszStrings[0] = g_sServiceName;
			lpszStrings[1] = sBuf;

			WORD eType = EVENTLOG_INFORMATION_TYPE;
			switch ( eLevel )
			{
				case LOG_FATAL:		eType = EVENTLOG_ERROR_TYPE; break;
				case LOG_WARNING:	eType = EVENTLOG_WARNING_TYPE; break;
				case LOG_INFO:		eType = EVENTLOG_INFORMATION_TYPE; break;
			}

			ReportEvent ( hEventSource,
				eType,
				0,
				0,
				NULL,
				2,
				0,
				lpszStrings,
				NULL );

			DeregisterEventSource ( hEventSource );
		}

	} else
#endif
	{
		strcat ( sBuf, "\n" );

		lseek ( g_iLogFile, 0, SEEK_END );
		write ( g_iLogFile, sBuf, strlen(sBuf) );

		if ( g_bLogStdout && g_iLogFile!=STDOUT_FILENO )
		{
			write ( STDOUT_FILENO, sBuf, strlen(sBuf) );
		}
	}
}
