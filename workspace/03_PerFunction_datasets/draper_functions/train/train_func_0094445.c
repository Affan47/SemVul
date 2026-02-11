force_ibs_eilvt_setup(void)
{
	int offset;
	int ret;

	preempt_disable();

	for (offset = 1; offset < APIC_EILVT_NR_MAX; offset++) {
		if (get_eilvt(offset))
			break;
	}
	preempt_enable();

	if (offset == APIC_EILVT_NR_MAX) {
		printk(KERN_DEBUG "No EILVT entry available\n");
		return;
	}

	ret = setup_ibs_ctl(offset);
	if (ret)
		goto out;

	if (!ibs_eilvt_valid())
		goto out;

	pr_info("IBS: LVT offset %d assigned\n", offset);

	return;
out:
	preempt_disable();
	put_eilvt(offset);
	preempt_enable();
	return;
}
