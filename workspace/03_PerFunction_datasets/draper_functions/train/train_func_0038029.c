sighandler(int s, siginfo_t *info, void *ctxt)
{
	if (s == SIGCHLD) {
		int status;
		waitpid(info->si_pid, &status, WNOHANG|WUNTRACED);
		g_message("child %d is dead", info->si_pid);

		if (app_context.xdm) {
			XDMCPD *xdm = app_context.xdm;
			XSession *xs = session_lookup_pid(xdm, info->si_pid);
			if (xs) {
				g_message("Deleting session %d", xs->ssid);
				xdm->sessions = g_list_remove(xdm->sessions, xs);
				g_free(xs);
			}
		}
		return;
	}

	g_message("exiting");
	if (app_context.loop)
		g_main_loop_quit(app_context.loop);
}
