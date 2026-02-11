syslog_write(int level, char *fmt, ...)
{
	int tmperr = errno;
	va_list aptr;
	int loglvl, dbglvl;
	FILE *fp;
	time_t now;
	struct tm *t;
	char *logstr, buf[32], str[MAX_PATH_SIZE * 4];

	va_start(aptr, fmt);
#if defined(HAVE_VSNPRINTF)
	vsnprintf(str, sizeof(str), fmt, aptr);
#else
	vsprintf(str, fmt, aptr);
#endif
	va_end(aptr);

	switch (level) {
		case T_DBG:	loglvl = LOG_DEBUG;
				logstr = "TECH-DBG";
				dbglvl = 3;
				break;
		case T_INF:	loglvl = LOG_INFO;
				logstr = "TECH-INF";
				dbglvl = 2;
				break;
		case T_WRN:	loglvl = LOG_WARNING;
				logstr = "TECH-WRN";
				dbglvl = 1;
				break;
		case T_ERR:	loglvl = LOG_ERR;
				logstr = "TECH-ERR";
				dbglvl = 1;
				break;
		case T_FTL:	loglvl = LOG_CRIT;
				logstr = "TECH-FTL";
				dbglvl = 1;
				break;

		case U_DBG:	loglvl = LOG_DEBUG;
				logstr = "USER-DBG";
				dbglvl = 3;
				break;
		case U_INF:	loglvl = LOG_INFO;
				logstr = "USER-INF";
				dbglvl = 2;
				break;
		case U_WRN:	loglvl = LOG_WARNING;
				logstr = "USER-WRN";
				dbglvl = 1;
				break;
		case U_ERR:	loglvl = LOG_ERR;
				logstr = "USER-ERR";
				dbglvl = 1;
				break;
		case U_FTL:	loglvl = LOG_CRIT;
				logstr = "USER-FTL";
				dbglvl = 1;
				break;

		default:	loglvl = LOG_CRIT;
				logstr = "TECH-FLT";
				dbglvl = 1;
	}

#if defined(COMPILE_DEBUG)
	debug(dbglvl, "%s %s", logstr, str);
#endif

	if (log_level < loglvl) {
		errno = tmperr;
		return;
	}

	if (log_syslog) {
		syslog(loglvl, "%s %s", logstr, str);
		errno = tmperr;
		return;
	}

	if ((fp = (log_file ? log_file : log_pipe)) == NULL) {
		errno = tmperr;
		return;
	}

	time(&now);
	t = localtime(&now);
#if defined(HAVE_SNPRINTF)
	snprintf(buf, sizeof(buf), "%02d/%02d-%02d:%02d:%02d",
			t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
#else
	sprintf(buf, "%02d/%02d-%02d:%02d:%02d",
			t->tm_mon + 1, t->tm_mday,
			t->tm_hour, t->tm_min, t->tm_sec);
#endif
	fprintf(fp, "%s [%d] <%s> %s %s\n", misc_getprog(),
				(int) getpid(), buf, logstr, str);
	fflush(fp);

	errno = tmperr;
}
