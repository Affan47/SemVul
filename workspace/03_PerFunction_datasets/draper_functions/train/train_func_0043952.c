ast_log_vsyslog(struct logmsg *msg)
{
	char buf[BUFSIZ];
	int syslog_level = ast_syslog_priority_from_loglevel(msg->level);
	char call_identifier_str[13];

	if (msg->callid) {
		snprintf(call_identifier_str, sizeof(call_identifier_str), "[C-%08x]", msg->callid->call_identifier);
	} else {
		call_identifier_str[0] = '\0';
	}

	if (syslog_level < 0) {

		fprintf(stderr, "ast_log_vsyslog called with bogus level: %d\n", msg->level);
		return;
	}

	snprintf(buf, sizeof(buf), "%s[%d]%s: %s:%d in %s: %s",
		 levels[msg->level], msg->lwp, call_identifier_str, msg->file, msg->line, msg->function, msg->message);

	term_strip(buf, buf, strlen(buf) + 1);
	syslog(syslog_level, "%s", buf);
}
