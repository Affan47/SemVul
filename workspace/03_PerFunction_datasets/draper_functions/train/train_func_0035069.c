sys_exit(tcp)
struct tcb *tcp;
{
	if (exiting(tcp)) {
		fprintf(stderr, "_exit returned!\n");
		return -1;
	}

	tprintf("%ld) ", tcp->u_arg[0]);
	tabto(acolumn);
	tprintf("= ?");
	printtrailer();
	return 0;
}
