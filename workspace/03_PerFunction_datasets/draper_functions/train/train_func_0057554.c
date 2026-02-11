sig_stats(int signo)
{
	do_sync = 1;
	do_stats = 1;
	if (in_poll)
		siglongjmp(env, 1);
}
