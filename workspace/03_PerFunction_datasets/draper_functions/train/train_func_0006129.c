sys_sethostname(tcp)
struct tcb *tcp;
{
	if (entering(tcp)) {
		printpathn(tcp, tcp->u_arg[0], tcp->u_arg[1]);
		tprintf(", %lu", tcp->u_arg[1]);
	}
	return 0;
}
