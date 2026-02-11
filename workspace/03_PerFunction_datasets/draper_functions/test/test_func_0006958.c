amdgpu_dpm_print_ps_status(struct amdgpu_device *adev,
				struct amdgpu_ps *rps)
{
	printk("\tstatus: ");
	if (rps == adev->pm.dpm.current_ps)
		printk("c ");
	if (rps == adev->pm.dpm.requested_ps)
		printk("r ");
	if (rps == adev->pm.dpm.boot_ps)
		printk("b ");
	printk("\n");
}
