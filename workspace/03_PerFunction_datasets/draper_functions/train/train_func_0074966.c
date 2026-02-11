setproctitle(const char *fmt, ...)
{
#if SPT_TYPE != SPT_NONE
	va_list ap;
	char ptitle[1024];
	size_t len;
	size_t argvlen;
#if SPT_TYPE == SPT_PSTAT
	union pstun pst;
#endif

#if SPT_TYPE == SPT_REUSEARGV
	if (argv_env_len <= 0)
		return;
#endif

	va_start(ap, fmt);
	if (fmt != NULL) {
		vsnprintf(ptitle, sizeof(ptitle) , fmt, ap);
	}
	va_end(ap);

#if SPT_TYPE == SPT_PSTAT
	pst.pst_command = ptitle;
	pstat(PSTAT_SETCMD, pst, strlen(ptitle), 0, 0);
#elif SPT_TYPE == SPT_REUSEARGV
	len = strlcpy(argv_start, ptitle, argv_env_len);
	argvlen = len > argv_len ? argv_env_len : argv_len;
	for(; len < argvlen; len++)
		argv_start[len] = SPT_PADCHAR;
#endif

#endif
}
