signal_handler(int sig)
{
	switch (sig)
	{
		case SIGHUP:
			log_message(STREAM_MAIN, MSG_WARN, "Received SIGHUP signal.\n");
			got_hup = 1;
			break;
		case SIGTERM:
			log_message(STREAM_MAIN, MSG_WARN, "Received SIGTERM signal.\n");
			log_message(STREAM_MAIN, MSG_GOOD, "Cleaning up\n");
			free_system();
			log_message(STREAM_MAIN, MSG_GOOD, "done.\n");


			unlink(option_pid_file);

			exit(EXIT_SUCCESS);
			break;
		default:
			log_message(STREAM_MAIN, MSG_WARN, "Unhandled signal (%d) %s\n", sig, strsignal(sig));
			break;
	}
}
