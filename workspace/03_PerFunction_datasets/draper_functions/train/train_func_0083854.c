sys_renameat(struct tcb *tcp)
{
	if (entering(tcp)) {
		print_dirfd(tcp->u_arg[0]);
		printpath(tcp, tcp->u_arg[1]);
		tprintf(", ");
		print_dirfd(tcp->u_arg[2]);
		printpath(tcp, tcp->u_arg[3]);
	}
	return 0;
}
