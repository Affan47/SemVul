sys_epoll_ctl(struct tcb *tcp)
{
	if (entering(tcp)) {
		tprintf("%ld, ", tcp->u_arg[0]);
		printxval(epollctls, tcp->u_arg[1], "EPOLL_CTL_???");
		tprintf(", %ld, ", tcp->u_arg[2]);
		if (tcp->u_arg[3] == 0)
			tprintf("NULL");
		else {
#ifdef HAVE_SYS_EPOLL_H
			struct epoll_event ev;
			if (umove(tcp, tcp->u_arg[3], &ev) == 0)
				print_epoll_event(&ev);
			else
#endif
				tprintf("{...}");
		}
	}
	return 0;
}
