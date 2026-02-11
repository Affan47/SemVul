gmc_v7_0_init_golden_registers(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		amdgpu_program_register_sequence(adev,
						 iceland_mgcg_cgcg_init,
						 (const u32)ARRAY_SIZE(iceland_mgcg_cgcg_init));
		amdgpu_program_register_sequence(adev,
						 golden_settings_iceland_a11,
						 (const u32)ARRAY_SIZE(golden_settings_iceland_a11));
		break;
	default:
		break;
	}
}
