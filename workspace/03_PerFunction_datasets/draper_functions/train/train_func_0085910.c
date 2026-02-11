ipath_signal_procs(struct ipath_devdata *dd, int sig)
{
	int i, sub, any = 0;
	struct pid *pid;
	unsigned long flags;

	if (!dd->ipath_pd)
		return 0;

	spin_lock_irqsave(&dd->ipath_uctxt_lock, flags);
	for (i = 1; i < dd->ipath_cfgports; i++) {
		if (!dd->ipath_pd[i] || !dd->ipath_pd[i]->port_cnt)
			continue;
		pid = dd->ipath_pd[i]->port_pid;
		if (!pid)
			continue;

		dev_info(&dd->pcidev->dev, "context %d in use "
			  "(PID %u), sending signal %d\n",
			  i, pid_nr(pid), sig);
		kill_pid(pid, sig, 1);
		any++;
		for (sub = 0; sub < INFINIPATH_MAX_SUBPORT; sub++) {
			pid = dd->ipath_pd[i]->port_subpid[sub];
			if (!pid)
				continue;
			dev_info(&dd->pcidev->dev, "sub-context "
				"%d:%d in use (PID %u), sending "
				"signal %d\n", i, sub, pid_nr(pid), sig);
			kill_pid(pid, sig, 1);
			any++;
		}
	}
	spin_unlock_irqrestore(&dd->ipath_uctxt_lock, flags);
	return any;
}
