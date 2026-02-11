amd_ibs_init(void)
{
	u32 caps;
	int ret = -EINVAL;

	caps = __get_ibs_caps();
	if (!caps)
		return -ENODEV;

	ibs_eilvt_setup();

	if (!ibs_eilvt_valid())
		goto out;

	perf_ibs_pm_init();
	cpu_notifier_register_begin();
	ibs_caps = caps;

	smp_mb();
	smp_call_function(setup_APIC_ibs, NULL, 1);
	__perf_cpu_notifier(perf_ibs_cpu_notifier);
	cpu_notifier_register_done();

	ret = perf_event_ibs_init();
out:
	if (ret)
		pr_err("Failed to setup IBS, %d\n", ret);
	return ret;
}
