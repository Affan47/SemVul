stop_keepalived(void)
{
	log_message(LOG_INFO, "Stopping " VERSION_STRING);

	signal_handler_destroy();
	thread_destroy_master(master);

	pidfile_rm(main_pidfile);

	if (daemon_mode & 1 || !daemon_mode)
		pidfile_rm(vrrp_pidfile);

	if (daemon_mode & 2 || !daemon_mode)
		pidfile_rm(checkers_pidfile);

#ifdef _DEBUG_
	keepalived_free_final("Parent process");
#endif
}
