ci_program_display_gap(struct amdgpu_device *adev)
{
	u32 tmp = RREG32_SMC(ixCG_DISPLAY_GAP_CNTL);
	u32 pre_vbi_time_in_us;
	u32 frame_time_in_us;
	u32 ref_clock = adev->clock.spll.reference_freq;
	u32 refresh_rate = amdgpu_dpm_get_vrefresh(adev);
	u32 vblank_time = amdgpu_dpm_get_vblank_time(adev);

	tmp &= ~CG_DISPLAY_GAP_CNTL__DISP_GAP_MASK;
	if (adev->pm.dpm.new_active_crtc_count > 0)
		tmp |= (AMDGPU_PM_DISPLAY_GAP_VBLANK_OR_WM << CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT);
	else
		tmp |= (AMDGPU_PM_DISPLAY_GAP_IGNORE << CG_DISPLAY_GAP_CNTL__DISP_GAP__SHIFT);
	WREG32_SMC(ixCG_DISPLAY_GAP_CNTL, tmp);

	if (refresh_rate == 0)
		refresh_rate = 60;
	if (vblank_time == 0xffffffff)
		vblank_time = 500;
	frame_time_in_us = 1000000 / refresh_rate;
	pre_vbi_time_in_us =
		frame_time_in_us - 200 - vblank_time;
	tmp = pre_vbi_time_in_us * (ref_clock / 100);

	WREG32_SMC(ixCG_DISPLAY_GAP_CNTL2, tmp);
	ci_write_smc_soft_register(adev, offsetof(SMU7_SoftRegisters, PreVBlankGap), 0x64);
	ci_write_smc_soft_register(adev, offsetof(SMU7_SoftRegisters, VBlankTimeout), (frame_time_in_us - pre_vbi_time_in_us));


	ci_notify_smc_display_change(adev, (adev->pm.dpm.new_active_crtc_count == 1));

}
