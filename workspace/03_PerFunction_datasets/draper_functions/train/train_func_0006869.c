hibernation_restore(int platform_mode)
{
	int error;

	pm_prepare_console();
	suspend_console();
	pm_restrict_gfp_mask();
	error = dpm_suspend_start(PMSG_QUIESCE);
	if (!error) {
		error = resume_target_kernel(platform_mode);


		BUG_ON(!error);
	}
	dpm_resume_end(PMSG_RECOVER);
	pm_restore_gfp_mask();
	resume_console();
	pm_restore_console();
	return error;
}
