do_ptrace(int request, struct tcb *tcp, void *addr, void *data)
{
	long l;

	errno = 0;
	l = ptrace(request, tcp->pid, addr, (long) data);


	if (errno == ESRCH)
		tcp->ptrace_errno = ESRCH;
	return l;
}
