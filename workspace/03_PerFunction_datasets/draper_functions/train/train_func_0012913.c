append_log(FILE * fp, const char * entity, int entity_pid
,	TIME_T timestamp, const char * pristr, const char * msg)
{
	static int		got_uname = FALSE;
	static struct utsname	un;

	if (!syslogformatfile) {
		print_logline(fp, entity, entity_pid, timestamp, pristr, msg);
		return;
	}
	if (!got_uname) {
		uname(&un);
	}


	fprintf(fp, "%s %s %s: [%d]: %s%s%s\n"
	,	syslog_timestamp(timestamp)
	,	un.nodename, entity, entity_pid
	,	(pristr ? pristr : "")
	,	(pristr ? ": " : "")
	,	msg);
}
