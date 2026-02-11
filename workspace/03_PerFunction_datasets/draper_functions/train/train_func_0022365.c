main (int argc, char *argv[])
{
	INIT_GLOBALS();
	command_line (argc, argv);


	if (Service_Type == NO_TYPE) {
		if (inetd_child ())
			Service_Type = INETD;
		else
			Service_Type = DAEMON;
	}

	if (Service_Type == INETD) {
		openlog ("in.ident2", LOG_PID, LOG_AUTH);
		child_service (STDIN_FILENO, STDOUT_FILENO);
		closelog ();
	}
	else
		daemon_service ();

	return 0;
}
