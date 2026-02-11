signal_trampoline_extended(int signo, siginfo_t *si, void *u)
{
	static volatile sig_atomic_t extended;
	sigset_t set;

	in_signal_handler++;
	extended++;


	if (-1 == sigpending(&set)) {
		s_warning("%s: sigpending() failed: %m", G_STRFUNC);
	} else if (extended <= 2) {
		int i;

		for (i = 1; i < SIG_COUNT; i++) {
			if (sigismember(&set, i)) {
				s_warning("%s: signal %s still pending",
					G_STRFUNC, signal_name(i));
			}
		}
	}


	{
		static char data[512];


		if (extended > 1) {
			if (2 == extended) {
				sig_exception_format(data, sizeof data, signo, si, u, TRUE);
				s_minicrit("%s", data);
				crash_set_error(data);
				crash_abort();
			} else if (3 == extended) {
				abort();
			} else {
				_exit(EXIT_FAILURE);
			}
		} else {
			sig_exception_format(data, sizeof data, signo, si, u, FALSE);
			s_critical("%s", data);
			crash_set_error(data);
		}
	}

	in_signal_handler--;
	signal_trampoline(signo);
}
