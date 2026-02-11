aipd_start (NMDevice *self, NMDeviceStateReason *reason)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);
	const char *iface = nm_device_get_iface (self);
	char *argv[6], *cmdline;
	const char **aipd_binary = NULL;
	static const char *aipd_paths[] = {
		"/usr/sbin/avahi-autoipd",
		"/usr/local/sbin/avahi-autoipd",
		NULL
	};
	int i = 0;
	GError *error = NULL;

	aipd_cleanup (self);


	aipd_binary = aipd_paths;
	while (*aipd_binary != NULL) {
		if (g_file_test (*aipd_binary, G_FILE_TEST_EXISTS))
			break;
		aipd_binary++;
	}

	if (!*aipd_binary) {
		nm_log_warn (LOGD_DEVICE | LOGD_AUTOIP4,
		             "Activation (%s) Stage 3 of 5 (IP Configure Start) failed"
		             " to start avahi-autoipd: not found", iface);
		*reason = NM_DEVICE_STATE_REASON_AUTOIP_START_FAILED;
		return NM_ACT_STAGE_RETURN_FAILURE;
	}

	argv[i++] = (char *) (*aipd_binary);
	argv[i++] = "--script";
	argv[i++] = LIBEXECDIR "/nm-avahi-autoipd.action";
	if (nm_logging_level_enabled (LOGL_DEBUG))
		argv[i++] = "--debug";
	argv[i++] = (char *) nm_device_get_ip_iface (self);
	argv[i++] = NULL;

	cmdline = g_strjoinv (" ", argv);
	nm_log_dbg (LOGD_AUTOIP4, "running: %s", cmdline);
	g_free (cmdline);

	if (!g_spawn_async ("/", argv, NULL, G_SPAWN_DO_NOT_REAP_CHILD,
	                    &aipd_child_setup, NULL, &(priv->aipd_pid), &error)) {
		nm_log_warn (LOGD_DEVICE | LOGD_AUTOIP4,
		             "Activation (%s) Stage 3 of 5 (IP Configure Start) failed"
		             " to start avahi-autoipd: %s",
		             iface,
		             error && error->message ? error->message : "(unknown)");
		g_clear_error (&error);
		aipd_cleanup (self);
		return NM_ACT_STAGE_RETURN_FAILURE;
	}

	nm_log_info (LOGD_DEVICE | LOGD_AUTOIP4,
	             "Activation (%s) Stage 3 of 5 (IP Configure Start) started"
	             " avahi-autoipd...", iface);


	priv->aipd_watch = g_child_watch_add (priv->aipd_pid, aipd_watch_cb, self);


	priv->aipd_timeout = g_timeout_add_seconds (20, aipd_timeout_cb, self);

	return NM_ACT_STAGE_RETURN_POSTPONE;
}
