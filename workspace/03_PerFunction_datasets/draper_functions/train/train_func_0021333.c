do_eventfd(struct tcb *tcp, int flags_arg)
{
	if (entering(tcp)) {
		tprintf("%lu", tcp->u_arg[0]);
		if (flags_arg >= 0) {
			tprintf(", ");
			printflags(open_mode_flags, tcp->u_arg[flags_arg], "O_???");
		}
	}
	return 0;
}
