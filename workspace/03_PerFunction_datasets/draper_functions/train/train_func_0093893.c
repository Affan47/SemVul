print_track(const char *s, struct track *t)
{
	if (!t->addr)
		return;

	pr_err("INFO: %s in %pS age=%lu cpu=%u pid=%d\n",
	       s, (void *)t->addr, jiffies - t->when, t->cpu, t->pid);
#ifdef CONFIG_STACKTRACE
	{
		int i;
		for (i = 0; i < TRACK_ADDRS_COUNT; i++)
			if (t->addrs[i])
				pr_err("\t%pS\n", (void *)t->addrs[i]);
			else
				break;
	}
#endif
}
