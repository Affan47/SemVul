create_image(int platform_mode)
{
	int error;

	error = dpm_suspend_end(PMSG_FREEZE);
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to power down, "
			"aborting hibernation\n");
		return error;
	}

	error = platform_pre_snapshot(platform_mode);
	if (error || hibernation_test(TEST_PLATFORM))
		goto Platform_finish;

	error = disable_nonboot_cpus();
	if (error || hibernation_test(TEST_CPUS))
		goto Enable_cpus;

	local_irq_disable();

	error = syscore_suspend();
	if (error) {
		printk(KERN_ERR "PM: Some system devices failed to power down, "
			"aborting hibernation\n");
		goto Enable_irqs;
	}

	if (hibernation_test(TEST_CORE) || pm_wakeup_pending())
		goto Power_up;

	in_suspend = 1;
	save_processor_state();
	trace_suspend_resume(TPS("machine_suspend"), PM_EVENT_HIBERNATE, true);
	error = swsusp_arch_suspend();

	restore_processor_state();
	trace_suspend_resume(TPS("machine_suspend"), PM_EVENT_HIBERNATE, false);
	if (error)
		printk(KERN_ERR "PM: Error %d creating hibernation image\n",
			error);
	if (!in_suspend)
		events_check_enabled = false;

	platform_leave(platform_mode);

 Power_up:
	syscore_resume();

 Enable_irqs:
	local_irq_enable();

 Enable_cpus:
	enable_nonboot_cpus();

 Platform_finish:
	platform_finish(platform_mode);

	dpm_resume_start(in_suspend ?
		(error ? PMSG_RECOVER : PMSG_THAW) : PMSG_RESTORE);

	return error;
}
