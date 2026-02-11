make_logchannel(const char *channel, const char *components, int lineno)
{
	struct logchannel *chan;
	char *facility;
	struct ast_tm tm;
	struct timeval now = ast_tvnow();
	char datestring[256];

	if (ast_strlen_zero(channel) || !(chan = ast_calloc(1, sizeof(*chan) + strlen(components) + 1)))
		return NULL;

	strcpy(chan->components, components);
	chan->lineno = lineno;

	if (!strcasecmp(channel, "console")) {
		chan->type = LOGTYPE_CONSOLE;
	} else if (!strncasecmp(channel, "syslog", 6)) {


		facility = strchr(channel, '.');
		if (!facility++ || !facility) {
			facility = "local0";
		}

		chan->facility = ast_syslog_facility(facility);

		if (chan->facility < 0) {
			fprintf(stderr, "Logger Warning: bad syslog facility in logger.conf\n");
			ast_free(chan);
			return NULL;
		}

		chan->type = LOGTYPE_SYSLOG;
		ast_copy_string(chan->filename, channel, sizeof(chan->filename));
		openlog("asterisk", LOG_PID, chan->facility);
	} else {
		if (!ast_strlen_zero(hostname)) {
			snprintf(chan->filename, sizeof(chan->filename), "%s/%s.%s",
				 channel[0] != '/' ? ast_config_AST_LOG_DIR : "", channel, hostname);
		} else {
			snprintf(chan->filename, sizeof(chan->filename), "%s/%s",
				 channel[0] != '/' ? ast_config_AST_LOG_DIR : "", channel);
		}
		if (!(chan->fileptr = fopen(chan->filename, "a"))) {


			ast_console_puts_mutable("ERROR: Unable to open log file '", __LOG_ERROR);
			ast_console_puts_mutable(chan->filename, __LOG_ERROR);
			ast_console_puts_mutable("': ", __LOG_ERROR);
			ast_console_puts_mutable(strerror(errno), __LOG_ERROR);
			ast_console_puts_mutable("'\n", __LOG_ERROR);
			ast_free(chan);
			return NULL;
		} else {

			ast_localtime(&now, &tm, NULL);
			ast_strftime(datestring, sizeof(datestring), dateformat, &tm);

			fprintf(chan->fileptr, "[%s] Asterisk %s built by %s @ %s on a %s running %s on %s\n",
				datestring, ast_get_version(), ast_build_user, ast_build_hostname,
				ast_build_machine, ast_build_os, ast_build_date);
			fflush(chan->fileptr);
		}
		chan->type = LOGTYPE_FILE;
	}
	chan->logmask = make_components(chan->components, lineno, &chan->verbosity);

	return chan;
}
