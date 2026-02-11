sigTerm(int sig)
{
	signal(sig, SIG_DFL);
	log(("SIGTERM...\n"));
	raise(sig);
}
