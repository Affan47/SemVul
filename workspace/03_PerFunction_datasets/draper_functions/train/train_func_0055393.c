do_suspend(void)
{
	int err;
	struct suspend_info si;

	shutting_down = SHUTDOWN_SUSPEND;

	err = freeze_processes();
	if (err) {
		pr_err("%s: freeze processes failed %d\n", __func__, err);
		goto out;
	}

	err = freeze_kernel_threads();
	if (err) {
		pr_err("%s: freeze kernel threads failed %d\n", __func__, err);
		goto out_thaw;
	}

	err = dpm_suspend_start(PMSG_FREEZE);
	if (err) {
		pr_err("%s: dpm_suspend_start %d\n", __func__, err);
		goto out_thaw;
	}

	printk(KERN_DEBUG "suspending xenstore...\n");
	xs_suspend();

	err = dpm_suspend_end(PMSG_FREEZE);
	if (err) {
		pr_err("dpm_suspend_end failed: %d\n", err);
		si.cancelled = 0;
		goto out_resume;
	}

	xen_arch_suspend();

	si.cancelled = 1;

	err = stop_machine(xen_suspend, &si, cpumask_of(0));


	if (!si.cancelled)
		xen_console_resume();

	raw_notifier_call_chain(&xen_resume_notifier, 0, NULL);

	dpm_resume_start(si.cancelled ? PMSG_THAW : PMSG_RESTORE);

	if (err) {
		pr_err("failed to start xen_suspend: %d\n", err);
		si.cancelled = 1;
	}

	xen_arch_resume();

out_resume:
	if (!si.cancelled)
		xs_resume();
	else
		xs_suspend_cancel();

	dpm_resume_end(si.cancelled ? PMSG_THAW : PMSG_RESTORE);

out_thaw:
	thaw_processes();
out:
	shutting_down = SHUTDOWN_INVALID;
}
