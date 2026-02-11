callsystem_exportdefaults(char** env[])
{
	static const char * callsystem_default_envvars[]={
		"USER", "LOGNAME", "HOME", "LANG", "LC_ALL", "LC_COLLATE", "LC_CTYPE",
		"LC_MESSAGES", "LC_MONETARY", "LC_NUMERIC", "LC_TIME", "PATH", "MANPATH",
		"INFOPATH", "CDPATH", "DISPLAY", "PWD", "SHELL", "TERM", "PAGER", "EDITOR",
		"VISUAL", "BROWSER", "NLSPATH", "LOCPATH", "TMPDIR",
		"HOSTALIASES", "TZ", "TZDIR", "TERMCAP",
		"COLUMNS", "LINES",
#ifdef unix
		"LD_LIBRARY_PATH", "LD_PRELOAD", "POSIXLY_CORRECT",


#elif defined(WIN32)

#endif
		0,
	};

	const char ** i;
	for( i =  callsystem_default_envvars;*i;++i)
	{
		if(callsystem_exportenv(env, *i) == -1 && errno == ENOMEM)
			return -1;
	}
	return 0;
}
