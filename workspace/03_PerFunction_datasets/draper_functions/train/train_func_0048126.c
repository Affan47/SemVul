dbgp_bulk_write(unsigned devnum, unsigned endpoint,
			 const char *bytes, int size)
{
	int ret;
	u32 addr;
	u32 pids, ctrl;

	if (size > DBGP_MAX_PACKET)
		return -1;

	addr = DBGP_EPADDR(devnum, endpoint);

	pids = readl(&ehci_debug->pids);
	pids = dbgp_pid_write_update(pids, USB_PID_OUT);

	ctrl = readl(&ehci_debug->control);
	ctrl = dbgp_len_update(ctrl, size);
	ctrl |= DBGP_OUT;
	ctrl |= DBGP_GO;

	dbgp_set_data(bytes, size);
	writel(addr, &ehci_debug->address);
	writel(pids, &ehci_debug->pids);
	ret = dbgp_wait_until_done(ctrl, DBGP_LOOPS);

	return ret;
}
