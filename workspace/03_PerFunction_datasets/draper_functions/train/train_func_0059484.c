nm_policy_set_system_hostname (const char *new_hostname, const char *msg)
{
	char old_hostname[HOST_NAME_MAX + 1];
	const char *name;
	int ret;

	if (new_hostname)
		g_warn_if_fail (strlen (new_hostname));

	old_hostname[HOST_NAME_MAX] = '\0';
	errno = 0;
	ret = gethostname (old_hostname, HOST_NAME_MAX);
	if (ret != 0) {
		nm_log_warn (LOGD_DNS, "couldn't get the system hostname: (%d) %s",
		             errno, strerror (errno));
	} else {

		if (   (new_hostname && !strcmp (old_hostname, new_hostname))
		    || (!new_hostname && !strcmp (old_hostname, FALLBACK_HOSTNAME4)))
			return FALSE;
	}

	name = (new_hostname && strlen (new_hostname)) ? new_hostname : FALLBACK_HOSTNAME4;

	nm_log_info (LOGD_DNS, "Setting system hostname to '%s' (%s)", name, msg);
	ret = sethostname (name, strlen (name));
	if (ret != 0) {
		nm_log_warn (LOGD_DNS, "couldn't set the system hostname to '%s': (%d) %s",
		             name, errno, strerror (errno));
	}

	return (ret == 0);
}
