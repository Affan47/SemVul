do_signals(struct signal *signals, int num_signals, int which)
{
    struct sigaction act;
    sigset_t mask;
    int error = 0;
    int i;

    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;

    for (i = 0; i < num_signals; i++) {
	struct signal *s = &signals[i];

	if (s->which != which)
	    continue;

	switch (s->action) {
	case SSA_IGNORE:
	    act.sa_handler = SIG_IGN;
	    if (sigaction(s->signum, &act, &s->old_act) < 0) {
		G_warning(_("G_spawn: unable to reset signal %d"), s->signum);
		error = 1;
	    }
	    else
		s->valid = 1;
	    break;
	case SSA_DEFAULT:
	    act.sa_handler = SIG_DFL;
	    if (sigaction(s->signum, &act, &s->old_act) < 0) {
		G_warning(_("G_spawn: unable to ignore signal %d"),
			  s->signum);
		error = 1;
	    }
	    else
		s->valid = 1;
	    break;
	case SSA_BLOCK:
	    sigemptyset(&mask);
	    sigaddset(&mask, s->signum);
	    if (sigprocmask(SIG_BLOCK, &mask, &s->old_mask) < 0) {
		G_warning(_("G_spawn: unable to block signal %d"), s->signum);
		error = 1;
	    }
	    break;
	case SSA_UNBLOCK:
	    sigemptyset(&mask);
	    sigaddset(&mask, s->signum);
	    if (sigprocmask(SIG_UNBLOCK, &mask, &s->old_mask) < 0) {
		G_warning(_("G_spawn: unable to unblock signal %d"),
			  s->signum);
		error = 1;
	    }
	    else
		s->valid = 1;
	    break;
	}
    }

    return !error;
}
