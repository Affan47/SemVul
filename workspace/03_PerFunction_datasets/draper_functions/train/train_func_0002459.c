sys_rt_sigsuspend(struct tcb *tcp)
{
	if (entering(tcp)) {
		sigset_t sigm;
		if (copy_sigset_len(tcp, tcp->u_arg[0], &sigm, tcp->u_arg[1]) < 0)
			tprintf("[?]");
		else
			printsigmask(&sigm, 1);
	}
	return 0;
}
