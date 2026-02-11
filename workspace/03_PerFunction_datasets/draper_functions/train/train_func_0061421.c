sys_gettimeofday(tcp)
struct tcb *tcp;
{
	if (exiting(tcp)) {
		if (syserror(tcp)) {
			tprintf("%#lx, %#lx",
				tcp->u_arg[0], tcp->u_arg[1]);
			return 0;
		}
		printtv(tcp, tcp->u_arg[0]);
#ifndef SVR4
		tprintf(", ");
		printtv(tcp, tcp->u_arg[1]);
#endif
	}
	return 0;
}
