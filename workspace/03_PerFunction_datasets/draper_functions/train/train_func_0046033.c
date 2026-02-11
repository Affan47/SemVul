sys_sigsuspend(struct tcb *tcp)
{
	if (entering(tcp)) {
		sigset_t sigm;
		long_to_sigset(tcp->u_arg[2], &sigm);
		printsigmask(&sigm, 0);
	}
	return 0;
}
