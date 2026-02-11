gkr_daemon_startup_steps (const gchar *components)
{
	g_assert (components);


#ifdef WITH_SSH
	if (strstr (components, GKD_COMP_SSH)) {
		if (ssh_started) {
			g_message ("The SSH agent was already initialized");
		} else {
			ssh_started = TRUE;
			if (!gkd_daemon_startup_ssh ()) {
				ssh_started = FALSE;
				return FALSE;
			}
		}
	}
#endif

#ifdef WITH_GPG
	if (strstr (components, GKD_COMP_GPG)) {
		if (gpg_started) {
			g_message ("The GPG agent was already initialized");
		} else {
			gpg_started = TRUE;
			if (!gkd_daemon_startup_gpg ()) {
				gpg_started = FALSE;
				return FALSE;
			}
		}
	}
#endif

	return TRUE;
}
