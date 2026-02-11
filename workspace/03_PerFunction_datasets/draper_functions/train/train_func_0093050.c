sys_capset(tcp)
struct tcb *tcp;
{
	static cap_user_header_t       arg0 = NULL;
	static cap_user_data_t         arg1 = NULL;

	if(entering(tcp)) {
		if (!arg0) {
			if ((arg0 = malloc(sizeof(*arg0))) == NULL) {
				fprintf(stderr, "out of memory\n");
				tprintf("%#lx, %#lx", tcp->u_arg[0], tcp->u_arg[1]);
				return -1;
			}
		}
		if (!arg1) {
			if ((arg1 = malloc(sizeof(*arg1))) == NULL) {
				fprintf(stderr, "out of memory\n");
				tprintf("%#lx, %#lx", tcp->u_arg[0], tcp->u_arg[1]);
				return -1;
			}
		}

		if (!tcp->u_arg[0])
			tprintf("NULL");
		else if (!verbose(tcp))
			tprintf("%#lx", tcp->u_arg[0]);
		else if (umoven(tcp, tcp->u_arg[0], sizeof(*arg0), (char *) arg0) < 0)
			tprintf("???");
		else {
			tprintf("%#x, %d", arg0->version, arg0->pid);
		}
		tprintf(", ");
		if (!tcp->u_arg[1])
			tprintf("NULL");
		else if (!verbose(tcp))
			tprintf("%#lx", tcp->u_arg[1]);
		else if (umoven(tcp, tcp->u_arg[1], sizeof(*arg1), (char *) arg1) < 0)
			tprintf("???");
		else {
			tprintf("{");
			printflags(capabilities, arg1->effective, "CAP_???");
			tprintf(", ");
			printflags(capabilities, arg1->permitted, "CAP_???");
			tprintf(", ");
			printflags(capabilities, arg1->inheritable, "CAP_???");
			tprintf("}");
		}
	}
	return 0;
}
