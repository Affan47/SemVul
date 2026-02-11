sys_flistxattr(struct tcb *tcp)
{
	if (entering(tcp)) {
		tprintf("%ld", tcp->u_arg[0]);
	} else {

		tprintf(", %p, %lu", (void *) tcp->u_arg[1], tcp->u_arg[2]);
	}
	return 0;
}
