signal_handler (int signo)
{
	static gboolean in_loop = FALSE;


	if (in_loop) {
		_exit (EXIT_FAILURE);
	}

	switch (signo) {
	case SIGTERM:
	case SIGINT:
		in_loop = TRUE;
		if (main_loop != NULL) {
			g_main_loop_quit (main_loop);
		} else {
			exit (0);
		}

	default:
		if (g_strsignal (signo)) {
			g_print ("\n");
			g_print ("Received signal:%d->'%s'\n",
			         signo,
			         g_strsignal (signo));
		}
		break;
	}
}
