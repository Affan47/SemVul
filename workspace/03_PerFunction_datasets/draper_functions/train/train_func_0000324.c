alarm_intr(int alnum)
{
    if (currently_testing >= blocks)
	return;

    signal(SIGALRM, alarm_intr);
    alarm(5);
    if (!currently_testing)
	return;

    printf("%lld... ", (unsigned long long)currently_testing);
    fflush(stdout);
}
