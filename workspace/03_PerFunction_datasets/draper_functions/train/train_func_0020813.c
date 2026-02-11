sys_ppoll(struct tcb *tcp)
{
	int rc = decode_poll(tcp, tcp->u_arg[2]);
	if (entering(tcp)) {
		print_timespec(tcp, tcp->u_arg[2]);
		tprintf(", ");
		print_sigset(tcp, tcp->u_arg[3], 0);
		tprintf(", %lu", tcp->u_arg[4]);
	}
	return rc;
}
