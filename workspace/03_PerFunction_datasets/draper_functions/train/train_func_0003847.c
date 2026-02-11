main (int argc, char * argv[])
{
	if (argc != 2) {
		g_critical("Need a PID to kill");
		return -1;
	}

#ifndef GLIB_VERSION_2_36
	g_type_init();
#endif

	g_unix_signal_add (SIGTERM, sigterm_graceful_exit, NULL);
	g_unix_signal_add (SIGHUP, sighup_dont_die, NULL);

	victim = atoi(argv[1]);

	restart_handler();

	mainloop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(mainloop);

	g_main_loop_unref(mainloop);

	return 0;
}
