output(LogLevel level, const char* tag, const char* func,
		const string& msg) throw ()
{
	int prio;
	switch (level)
	{
		case DEBUG: prio = LOG_DEBUG; break;
		case INFO: prio = LOG_INFO; break;
		case UNUSUAL: prio = LOG_NOTICE; break;
		case WARN: prio = LOG_WARNING; break;
		case ERR: prio = LOG_ERR; break;
		case CRIT: prio = LOG_CRIT; break;

		default: prio = LOG_WARNING; break;
	}
	syslog(prio, "%s %s: %.*s", tag, func, PFSTR(msg));
}
