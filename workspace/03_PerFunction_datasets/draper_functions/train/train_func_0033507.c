close_fds()
{
	struct rlimit rl;

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		die("getrlimit");
	for (unsigned int i = 3; i <= rl.rlim_max; ++i)
		close(i);
	close(0);
	open("/dev/null", O_RDWR);
	dup2(0, 1);
}
