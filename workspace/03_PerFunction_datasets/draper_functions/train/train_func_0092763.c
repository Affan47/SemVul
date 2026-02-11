sys_sched_setaffinity(struct tcb *tcp)
{
	if (entering(tcp)) {
		tprintf("%ld, %lu, ", tcp->u_arg[0], tcp->u_arg[1]);
		print_affinitylist(tcp, tcp->u_arg[2], tcp->u_arg[1]);
	}
	return 0;
}
