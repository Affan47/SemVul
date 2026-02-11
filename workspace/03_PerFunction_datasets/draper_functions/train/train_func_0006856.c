log_kmod(void *data, int priority, const char *file, int line,
		     const char *fn, const char *format, va_list args)
{
	const char *prioname = prio_to_str(priority);
	char *str;

	if (vasprintf(&str, format, args) < 0)
		return;

	if (log_use_syslog) {
#ifdef ENABLE_DEBUG
		syslog(priority, "%s: %s:%d %s() %s", prioname, file, line,
		       fn, str);
#else
		syslog(priority, "%s: %s", prioname, str);
#endif
	} else {
#ifdef ENABLE_DEBUG
		fprintf(stderr, "%s: %s: %s:%d %s() %s",
			program_invocation_short_name, prioname, file, line,
			fn, str);
#else
		fprintf(stderr, "%s: %s: %s", program_invocation_short_name,
			prioname, str);
#endif
	}

	free(str);
	(void)data;
}
