setup_signals (void)
{
	pthread_t signal_thread_id;
	sigset_t old_sig_mask;
	int status;

	sigemptyset (&signal_set);
	sigaddset (&signal_set, SIGHUP);
	sigaddset (&signal_set, SIGINT);
	sigaddset (&signal_set, SIGTERM);


	status = pthread_sigmask (SIG_BLOCK, &signal_set, &old_sig_mask);
	if (status != 0) {
		fprintf (stderr, _("Failed to set signal mask: %d"), status);
		return FALSE;
	}

	nm_save_original_signal_mask (old_sig_mask);


	status = pthread_create (&signal_thread_id, NULL, signal_handling_thread, NULL);
	if (status != 0) {
		fprintf (stderr, _("Failed to create signal handling thread: %d"), status);
		return FALSE;
	}

	return TRUE;
}
