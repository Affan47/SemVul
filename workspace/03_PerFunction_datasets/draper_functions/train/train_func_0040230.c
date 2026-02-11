child_watch_cb (GPid pid, gint status, PasswdHandler *passwd_handler)
{
	if (WIFEXITED (status)) {
		if (WEXITSTATUS (status) >= 255) {
			g_warning ("Child exited unexpectedly");
		}
	}

	free_passwd_resources (passwd_handler);
}
