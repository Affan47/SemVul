sys_clock_settime(tcp)
struct tcb *tcp;
{
	if (entering(tcp)) {
		printxval(clocknames, tcp->u_arg[0], "CLOCK_???");
		tprintf(", ");
		printtv(tcp, tcp->u_arg[1]);
	}
	return 0;
}
