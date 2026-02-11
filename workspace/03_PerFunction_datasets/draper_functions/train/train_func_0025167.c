parse_opt(const char *opt, char **ident, int *facility)
{
	char *str = _strdup(opt);
	char *ptr, *endptr;
	int n;
	const char *facility_name[] = {"daemon", "local0", "local1", "local2", "local3", "local4", "local5", "local6", "local7"};
	const int facility_num[] = {LOG_DAEMON, LOG_LOCAL0, LOG_LOCAL1, LOG_LOCAL2, LOG_LOCAL3, LOG_LOCAL4, LOG_LOCAL5, LOG_LOCAL6, LOG_LOCAL7};

	ptr = strchr(str, ',');
	if (ptr) {
		*ptr = 0;
		n = strtol(ptr + 1, &endptr, 10);
		if (*endptr) {
			for (n = 0; n < sizeof(facility_name); n++) {
				if (!strcasecmp(ptr + 1, facility_name[n]))
					break;
			}
			if (n == sizeof(facility_name))
				log_emerg("log_syslog: unknown facility name '%s'\n", ptr + 1);
			else
				*facility = facility_num[n];
		} else
			*facility = n;
	}

	*ident = str;
}
