audit_log_user_avc_message(int audit_fd, int type, const char *message,
	const char *hostname, const char *addr, const char *tty, uid_t uid)
{
	char buf[MAX_AUDIT_MESSAGE_LENGTH];
	char addrbuf[INET6_ADDRSTRLEN];
	static char exename[PATH_MAX*2] = "";
	char ttyname[TTY_PATH];
	int retval;

	if (audit_fd < 0)
		return 0;


	if (hostname && *hostname == 0)
		hostname = NULL;
	addrbuf[0] = 0;
	if (addr == NULL || strlen(addr) == 0)
		_resolve_addr(addrbuf, hostname);
	else
		strncat(addrbuf, addr, sizeof(addrbuf)-1);
	if (exename[0] == 0)
		_get_exename(exename, sizeof(exename));
	if (tty == NULL)
		tty = _get_tty(ttyname, TTY_PATH);
	else if (*tty == 0)
		tty = NULL;

	snprintf(buf, sizeof(buf),
	    "%s exe=%s sauid=%d hostname=%s addr=%s terminal=%s",
		message, exename, uid,
		hostname ? hostname : "?",
		addrbuf,
		tty ? tty : "?"
		);

	errno = 0;
	retval = audit_send_user_message( audit_fd, type, REAL_ERR, buf );
	if (retval == -EPERM && getuid() != 0) {
		syslog(LOG_ERR, "Can't send to audit system: %s %s",
			audit_msg_type_to_name(type), buf);
		return 0;
	}
	if ((retval < 1) && errno == 0)
		errno = retval;
	return retval;
}
