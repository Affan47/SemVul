skx_mce_check_error(struct notifier_block *nb, unsigned long val,
			       void *data)
{
	struct mce *mce = (struct mce *)data;
	struct decoded_addr res;
	struct mem_ctl_info *mci;
	char *type;

	if (get_edac_report_status() == EDAC_REPORTING_DISABLED)
		return NOTIFY_DONE;


	if ((mce->status & 0xefff) >> 7 != 1 || !(mce->status & MCI_STATUS_ADDRV))
		return NOTIFY_DONE;

	res.addr = mce->addr;
	if (!skx_decode(&res))
		return NOTIFY_DONE;
	mci = res.dev->imc[res.imc].mci;

	if (mce->mcgstatus & MCG_STATUS_MCIP)
		type = "Exception";
	else
		type = "Event";

	skx_mc_printk(mci, KERN_DEBUG, "HANDLING MCE MEMORY ERROR\n");

	skx_mc_printk(mci, KERN_DEBUG, "CPU %d: Machine Check %s: %Lx "
			  "Bank %d: %016Lx\n", mce->extcpu, type,
			  mce->mcgstatus, mce->bank, mce->status);
	skx_mc_printk(mci, KERN_DEBUG, "TSC %llx ", mce->tsc);
	skx_mc_printk(mci, KERN_DEBUG, "ADDR %llx ", mce->addr);
	skx_mc_printk(mci, KERN_DEBUG, "MISC %llx ", mce->misc);

	skx_mc_printk(mci, KERN_DEBUG, "PROCESSOR %u:%x TIME %llu SOCKET "
			  "%u APIC %x\n", mce->cpuvendor, mce->cpuid,
			  mce->time, mce->socketid, mce->apicid);

	skx_mce_output_error(mci, mce, &res);

	return NOTIFY_DONE;
}
