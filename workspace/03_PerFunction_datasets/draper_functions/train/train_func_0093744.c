sys_fadvise64_64(struct tcb *tcp)
{
	if (entering(tcp)) {
		int argn;
		tprintf("%ld, ", tcp->u_arg[0]);
#if defined ARM || defined POWERPC
		argn = printllval(tcp, "%lld, ", 2);
#else
		argn = printllval(tcp, "%lld, ", 1);
#endif
		argn = printllval(tcp, "%lld, ", argn);
#if defined ARM || defined POWERPC
		printxval(advise, tcp->u_arg[1], "POSIX_FADV_???");
#else
		printxval(advise, tcp->u_arg[argn], "POSIX_FADV_???");
#endif
	}
	return 0;
}
