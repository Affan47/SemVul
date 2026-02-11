__connman_service_auto_connect(void)
{
	DBG("");

	if (__connman_session_mode() == TRUE) {
		DBG("Session mode enabled: auto connect disabled");
		return;
	}

	if (autoconnect_timeout != 0)
		return;

	autoconnect_timeout = g_timeout_add_seconds(0, run_auto_connect, NULL);
}
