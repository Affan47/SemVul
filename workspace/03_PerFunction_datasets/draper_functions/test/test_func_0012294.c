sys_adjtimex(struct tcb *tcp)
{
	if (exiting(tcp)) {
		if (tcp->u_arg[0] == 0)
			tprintf("NULL");
		else if (syserror(tcp) || !verbose(tcp))
			tprintf("%#lx", tcp->u_arg[0]);
		else if (tprint_timex(tcp, tcp->u_arg[0]) < 0)
			tprintf("{...}");
		if (syserror(tcp))
			return 0;
		tcp->auxstr = xlookup(adjtimex_state, tcp->u_rval);
		if (tcp->auxstr)
			return RVAL_STR;
	}
	return 0;
}
