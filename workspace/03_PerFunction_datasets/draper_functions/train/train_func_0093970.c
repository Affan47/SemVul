wait_loop(unsigned long start, unsigned int max_delay,
		     unsigned int *seconds_waited)
{
	if (time_after(jiffies, start + (*seconds_waited+5)*HZ)) {
		if (!*seconds_waited)
			pr_warn("Waiting for devices to initialise: ");
		*seconds_waited += 5;
		pr_cont("%us...", max_delay - *seconds_waited);
		if (*seconds_waited == max_delay) {
			pr_cont("\n");
			return true;
		}
	}

	schedule_timeout_interruptible(HZ/10);

	return false;
}
