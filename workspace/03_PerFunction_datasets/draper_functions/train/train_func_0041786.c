sys_epoll_pwait(struct tcb *tcp)
{
	epoll_wait_common(tcp);
	if (exiting(tcp)) {
		tprintf(", ");
		print_sigset(tcp, tcp->u_arg[4], 0);
	}
	return 0;
}
