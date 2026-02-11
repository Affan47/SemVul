sys_sendfile64(struct tcb *tcp)
{
	if (entering(tcp)) {
		loff_t offset;

		printfd(tcp, tcp->u_arg[0]);
		tprintf(", ");
		printfd(tcp, tcp->u_arg[1]);
		tprintf(", ");
		if (!tcp->u_arg[2])
			tprintf("NULL");
		else if (umove(tcp, tcp->u_arg[2], &offset) < 0)
			tprintf("%#lx", tcp->u_arg[2]);
		else
			tprintf("[%llu]", (unsigned long long int) offset);
		tprintf(", %lu", tcp->u_arg[3]);
	}
	return 0;
}
