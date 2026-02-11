cl_signal_set_handler_mode(const cl_signal_mode_t *mode, sigset_t *set)
{
	size_t i;
	sigset_t our_set;
	sigset_t *use_set;

	use_set = (set) ? set : &our_set;

	for (i=0; mode[i].sig; ++i) {
		if(sigaddset(use_set, mode[i].sig) < 0) {
			cl_perror("cl_signal_set_handler_mode(): "
				"sigaddset() [signum=%d]", mode[i].sig);
			return(-1);
		}
	}

	if (sigprocmask(SIG_UNBLOCK, use_set, NULL) < 0) {
		cl_perror("cl_signal_set_handler_mode()"
		": sigprocmask()");
		return(-1);
	}

	for (i=0; mode[i].sig; ++i) {
		if(cl_signal_set_handler(mode[i].sig, mode[i]. handler
		,	use_set, SA_NOCLDSTOP, NULL) < 0) {
			cl_log(LOG_ERR, "cl_signal_set_handler_mode(): "
				"ha_set_sig_handler()");
			return(-1);
		}
		if(cl_signal_set_interrupt(mode[i].sig, mode[i].interrupt) < 0) {
			cl_log(LOG_ERR, "cl_signal_set_handler_mode(): "
				"hb_signal_interrupt()");
			return(-1);
		}
	}

	return(0);
}
