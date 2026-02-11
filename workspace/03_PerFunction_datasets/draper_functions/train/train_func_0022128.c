wait_tulip(struct initio_host * host)
{

	while (!((host->jsstatus0 = inb(host->addr + TUL_SStatus0))
		 & TSS_INT_PENDING))
			cpu_relax();

	host->jsint = inb(host->addr + TUL_SInt);
	host->phase = host->jsstatus0 & TSS_PH_MASK;
	host->jsstatus1 = inb(host->addr + TUL_SStatus1);

	if (host->jsint & TSS_RESEL_INT)
		return int_initio_resel(host);
	if (host->jsint & TSS_SEL_TIMEOUT)
		return int_initio_busfree(host);
	if (host->jsint & TSS_SCSIRST_INT)
		return int_initio_scsi_rst(host);

	if (host->jsint & TSS_DISC_INT) {
		if (host->flags & HCF_EXPECT_DONE_DISC) {
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			initio_unlink_busy_scb(host, host->active);
			host->active->hastat = 0;
			initio_append_done_scb(host, host->active);
			host->active = NULL;
			host->active_tc = NULL;
			host->flags &= ~HCF_EXPECT_DONE_DISC;
			outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);
			return -1;
		}
		if (host->flags & HCF_EXPECT_DISC) {
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0);
			host->active = NULL;
			host->active_tc = NULL;
			host->flags &= ~HCF_EXPECT_DISC;
			outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);
			return -1;
		}
		return int_initio_busfree(host);
	}

	if (host->jsint & (TSS_FUNC_COMP | TSS_BUS_SERV))
		return host->phase;
	return host->phase;
}
