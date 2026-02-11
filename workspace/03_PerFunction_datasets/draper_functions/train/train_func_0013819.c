share_init (void)
{
	int status;
	char *modules[] = { "ip_tables", "iptable_nat", "nf_nat_ftp", "nf_nat_irc",
	                    "nf_nat_sip", "nf_nat_tftp", "nf_nat_pptp", "nf_nat_h323",
	                    NULL };
	char **iter;

	if (!nm_utils_do_sysctl ("/proc/sys/net/ipv4/ip_forward", "1")) {
		nm_log_err (LOGD_SHARING, "Error starting IP forwarding: (%d) %s",
					errno, strerror (errno));
		return FALSE;
	}

	if (!nm_utils_do_sysctl ("/proc/sys/net/ipv4/ip_dynaddr", "1")) {
		nm_log_err (LOGD_SHARING, "error starting IP forwarding: (%d) %s",
					errno, strerror (errno));
	}

	for (iter = modules; *iter; iter++) {
		char *argv[3] = { "/sbin/modprobe", *iter, NULL };
		char *envp[1] = { NULL };
		GError *error = NULL;

		if (!g_spawn_sync ("/", argv, envp, G_SPAWN_STDOUT_TO_DEV_NULL | G_SPAWN_STDERR_TO_DEV_NULL,
		                   share_child_setup, NULL, NULL, NULL, &status, &error)) {
			nm_log_err (LOGD_SHARING, "error loading NAT module %s: (%d) %s",
			            *iter, error ? error->code : 0,
			            (error && error->message) ? error->message : "unknown");
			if (error)
				g_error_free (error);
		}
	}

	return TRUE;
}
