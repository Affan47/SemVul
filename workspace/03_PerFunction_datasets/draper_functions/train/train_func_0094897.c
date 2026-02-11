suspend_prepare(suspend_state_t state)
{
	int error;

	if (!sleep_state_supported(state))
		return -EPERM;

	pm_prepare_console();

	error = pm_notifier_call_chain(PM_SUSPEND_PREPARE);
	if (error)
		goto Finish;

	trace_suspend_resume(TPS("freeze_processes"), 0, true);
	error = suspend_freeze_processes();
	trace_suspend_resume(TPS("freeze_processes"), 0, false);
	if (!error)
		return 0;

	suspend_stats.failed_freeze++;
	dpm_save_failed_step(SUSPEND_FREEZE);
 Finish:
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
	return error;
}
