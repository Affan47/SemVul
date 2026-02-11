handle_ptrace_event(int status, struct tcb *tcp)
{
	if (status >> 16 == PTRACE_EVENT_VFORK ||
	    status >> 16 == PTRACE_EVENT_CLONE ||
	    status >> 16 == PTRACE_EVENT_FORK) {
		long childpid;

		if (do_ptrace(PTRACE_GETEVENTMSG, tcp, NULL, &childpid) < 0) {
			if (errno != ESRCH) {
				fprintf(stderr, "\
%s: handle_ptrace_event: ptrace cannot get new child's pid\n",
					progname);
				cleanup();
				exit(1);
			}
			return -1;
		}
		return handle_new_child(tcp, childpid, 0);
	}
	return 1;
}
