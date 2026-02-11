mgt_sigchld(const struct vev *e, int what)
{
	int status;
	struct vsb *vsb;
	pid_t r;

	(void)e;
	(void)what;

	if (ev_poker != NULL) {
		vev_del(mgt_evb, ev_poker);
		free(ev_poker);
	}
	ev_poker = NULL;

	r = waitpid(child_pid, &status, WNOHANG);
	if (r == 0 || (r == -1 && errno == ECHILD))
		return (0);
	assert(r == child_pid);
	vsb = VSB_new_auto();
	XXXAN(vsb);
	VSB_printf(vsb, "Child (%d) %s", r, status ? "died" : "ended");
	if (WIFEXITED(status) && WEXITSTATUS(status)) {
		VSB_printf(vsb, " status=%d", WEXITSTATUS(status));
		exit_status |= 0x20;
	}
	if (WIFSIGNALED(status)) {
		VSB_printf(vsb, " signal=%d", WTERMSIG(status));
		exit_status |= 0x40;
	}
#ifdef WCOREDUMP
	if (WCOREDUMP(status)) {
		VSB_printf(vsb, " (core dumped)");
		exit_status |= 0x80;
	}
#endif
	AZ(VSB_finish(vsb));
	REPORT(LOG_INFO, "%s", VSB_data(vsb));
	VSB_delete(vsb);

	if (heritage.panic_str[0] != '\0') {
		mgt_handle_panicstr(r);
		mgt_SHM_Destroy(1);
	} else {
		mgt_SHM_Destroy(0);
	}
	mgt_SHM_Create();

	child_pid = -1;

	if (child_state == CH_RUNNING) {
		child_state = CH_DIED;
		mgt_cli_stop_child();
		closex(&child_VCLI_Out);
		closex(&child_cli_in);
	}

	if (ev_listen != NULL) {
		vev_del(mgt_evb, ev_listen);
		free(ev_listen);
		ev_listen = NULL;
	}

	(void)child_listener(NULL, EV_RD);
	closex(&child_output);

	REPORT0(LOG_DEBUG, "Child cleanup complete");

	if (child_state == CH_DIED && mgt_param.auto_restart)
		start_child(NULL);
	else if (child_state == CH_DIED) {
		child_state = CH_STOPPED;
	} else if (child_state == CH_STOPPING)
		child_state = CH_STOPPED;

	return (0);
}
