dbgp_ehci_startup(void)
{
	u32 ctrl, cmd, status;
	int loop;


	ctrl = readl(&ehci_debug->control);
	ctrl |= DBGP_OWNER;
	ctrl &= ~(DBGP_ENABLED | DBGP_INUSE);
	writel(ctrl, &ehci_debug->control);
	udelay(1);

	dbgp_ehci_status("EHCI startup");

	cmd = readl(&ehci_regs->command);
	cmd &= ~(CMD_LRESET | CMD_IAAD | CMD_PSE | CMD_ASE | CMD_RESET);
	cmd |= CMD_RUN;
	writel(cmd, &ehci_regs->command);


	writel(FLAG_CF, &ehci_regs->configured_flag);


	loop = 1000;
	do {
		status = readl(&ehci_regs->status);
		if (!(status & STS_HALT))
			break;
		udelay(1);
	} while (--loop > 0);

	if (!loop) {
		dbgp_printk("ehci can not be started\n");
		return -ENODEV;
	}
	dbgp_printk("ehci started\n");
	return 0;
}
