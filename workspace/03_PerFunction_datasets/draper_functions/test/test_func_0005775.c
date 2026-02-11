run_arpspoof_until_successed(struct arp_spoof_info *asi)
{
	struct sigaction sa, sa_old;
	struct timespec timeout;
	int retval;

	if ((retval = find_asi_dst_mac(asi, "dst mac isn't known\n")) < 0)
		return retval;
	printf("CTRL-C to break\n");

	sa.sa_handler = run_arpspoof_intr;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, &sa_old);
	pthread_sigmask(SIG_BLOCK, &intr_mask, NULL);

	run_arpspoof = 1;
	while (arpspoof_test(asi) != 0 && run_arpspoof) {
		printf(".");
		fflush(stdout);
		force_arp_spoof(asi, 4);
		pthread_sigmask(SIG_UNBLOCK, &intr_mask, NULL);
		timeout.tv_sec = 5;
		timeout.tv_nsec = 0;
		nanosleep(&timeout, NULL);
		pthread_sigmask(SIG_BLOCK, &intr_mask, NULL);
	}
	if (!run_arpspoof)
		press_key("\n-- operation canceled - press any key> ");
	pthread_sigmask(SIG_UNBLOCK, &intr_mask, NULL);
	sigaction(SIGINT, &sa_old, NULL);
	return arpspoof_test(asi);
}
