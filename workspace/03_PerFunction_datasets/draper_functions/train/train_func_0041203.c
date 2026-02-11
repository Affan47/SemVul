dlm_user_daemon_available(void)
{


	if (!dlm_our_nodeid())
		return 0;


	if (dlm_monitor_unused)
		return 1;

	return atomic_read(&dlm_monitor_opened) ? 1 : 0;
}
