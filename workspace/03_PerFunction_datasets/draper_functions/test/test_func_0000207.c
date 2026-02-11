ns83820_run_bist(struct nic *nic __unused, const char *name,
			     u32 enable, u32 done, u32 fail)
{
	int timed_out = 0;
	long start;
	u32 status;
	int loops = 0;

	dprintf(("start %s\n", name))

	    start = currticks();

	writel(enable, ns->base + PTSCR);
	for (;;) {
		loops++;
		status = readl(ns->base + PTSCR);
		if (!(status & enable))
			break;
		if (status & done)
			break;
		if (status & fail)
			break;
		if ((currticks() - start) >= HZ) {
			timed_out = 1;
			break;
		}
	}

	if (status & fail)
	  printf("%s failed! (0x%hX & 0x%hX)\n", name, (unsigned int) status,
		 (unsigned int) fail);
	else if (timed_out)
		printf("run_bist %s timed out! (%hX)\n", name, (unsigned int) status);
	dprintf(("done %s in %d loops\n", name, loops));
}
