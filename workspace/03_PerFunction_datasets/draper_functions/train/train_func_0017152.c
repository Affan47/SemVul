wait_jobs()


{
    while (running_jobs > 0)
    {
	wait_signal();
	if (got_sigchld) tend_children();
	got_sigchld = 0;
	if (got_sigusr1) orderly_termination();
    }
}
