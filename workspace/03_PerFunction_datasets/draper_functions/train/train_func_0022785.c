signal_handler (int signo)
{
	switch (signo) {
		case SIGHUP:
		case SIGQUIT:
			logger (LOG_DBG, "INFO: received %s, ignoring.\n",
					strsignal (signo));
			break;

		case SIGINT:
		case SIGTERM:
			logger (LOG_DBG, "INFO: received %s, terminating.\n",
					strsignal (signo));
			terminate = 1;
			break;

		default:
			logger (LOG_ERR, "ERROR: received %s, unhandled.\n",
					strsignal (signo));
	}

	return;
}
