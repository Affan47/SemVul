ChangeLogging(void)

{

	if ( terminate == 1 )
		Terminate();


	Syslog(LOG_INFO, "klogd %s.%s, ---------- state change ----------\n", \
	       VERSION, PATCHLEVEL);


	if ( reload_symbols > 0 )
	{
		ReloadSymbols();
		return;
	}


	if ( caught_TSTP == 1 )
	{
		CloseLogSrc();
		logsrc = none;
		change_state = 0;
		return;
	}


	if ( logsrc != none )
	{
		Syslog(LOG_INFO, "Kernel logging re-started after SIGSTOP.");
		change_state = 0;
		return;
	}


	logsrc = GetKernelLogSrc();
	change_state = 0;
	return;
}
