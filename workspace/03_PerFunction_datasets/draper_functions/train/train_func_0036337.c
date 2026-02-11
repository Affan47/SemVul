kv_dpm_disable(struct amdgpu_device *adev)
{
	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_LOW_TO_HIGH);
	amdgpu_irq_put(adev, &adev->pm.dpm.thermal.irq,
		       AMDGPU_THERMAL_IRQ_HIGH_TO_LOW);

	amdgpu_kv_smc_bapm_enable(adev, false);

	if (adev->asic_type == CHIP_MULLINS)
		kv_enable_nb_dpm(adev, false);


	kv_dpm_powergate_acp(adev, false);
	kv_dpm_powergate_samu(adev, false);
	kv_dpm_powergate_vce(adev, false);
	kv_dpm_powergate_uvd(adev, false);

	kv_enable_smc_cac(adev, false);
	kv_enable_didt(adev, false);
	kv_clear_vc(adev);
	kv_stop_dpm(adev);
	kv_enable_ulv(adev, false);
	kv_reset_am(adev);

	kv_update_current_ps(adev, adev->pm.dpm.boot_ps);
}
