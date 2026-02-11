free_child(int pid)
{
	sigset_t nset, oset;
	struct child *cp = findchild(pid);
	sigemptyset(&nset);
	sigaddset(&nset, SIGCHLD);
	sigprocmask(SIG_BLOCK, &nset, &oset);

	if (cp->done)
		delchild(cp);
	else
		cp->free = 1;
	sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
}
