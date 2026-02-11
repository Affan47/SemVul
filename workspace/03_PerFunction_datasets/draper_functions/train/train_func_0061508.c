do_stop(void)
{
	char *what;
	struct pid_list *p;
	int killed = 0;

	if (cmdname) {
		if (ENABLE_FEATURE_CLEAN_UP) what = xstrdup(cmdname);
		if (!ENABLE_FEATURE_CLEAN_UP) what = cmdname;
	} else if (execname) {
		if (ENABLE_FEATURE_CLEAN_UP) what = xstrdup(execname);
		if (!ENABLE_FEATURE_CLEAN_UP) what = execname;
	} else if (pidfile) {
		what = xasprintf("process in pidfile '%s'", pidfile);
	} else if (userspec) {
		what = xasprintf("process(es) owned by '%s'", userspec);
	} else {
		bb_error_msg_and_die("internal error, please report");
	}

	if (!G.found_procs) {
		if (!QUIET)
			printf("no %s found; none killed\n", what);
		killed = -1;
		goto ret;
	}
	for (p = G.found_procs; p; p = p->next) {
		if (TEST || kill(p->pid, signal_nr) == 0) {
			killed++;
		} else {
			p->pid = 0;
			bb_perror_msg("warning: killing process %u", (unsigned)p->pid);
		}
	}
	if (!QUIET && killed) {
		printf("stopped %s (pid", what);
		for (p = G.found_procs; p; p = p->next)
			if (p->pid)
				printf(" %u", (unsigned)p->pid);
		puts(")");
	}
 ret:
	if (ENABLE_FEATURE_CLEAN_UP)
		free(what);
	return killed;
}
