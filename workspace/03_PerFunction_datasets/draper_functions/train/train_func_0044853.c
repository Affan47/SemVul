r100_mc_program(struct radeon_device *rdev)
{
	struct r100_mc_save save;


	r100_mc_stop(rdev, &save);
	if (rdev->flags & RADEON_IS_AGP) {
		WREG32(R_00014C_MC_AGP_LOCATION,
			S_00014C_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_00014C_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32(R_000170_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		if (rdev->family > CHIP_RV200)
			WREG32(R_00015C_AGP_BASE_2,
				upper_32_bits(rdev->mc.agp_base) & 0xff);
	} else {
		WREG32(R_00014C_MC_AGP_LOCATION, 0x0FFFFFFF);
		WREG32(R_000170_AGP_BASE, 0);
		if (rdev->family > CHIP_RV200)
			WREG32(R_00015C_AGP_BASE_2, 0);
	}

	if (r100_mc_wait_for_idle(rdev))
		dev_warn(rdev->dev, "Wait for MC idle timeout.\n");

	WREG32(R_000148_MC_FB_LOCATION,
		S_000148_MC_FB_START(rdev->mc.vram_start >> 16) |
		S_000148_MC_FB_TOP(rdev->mc.vram_end >> 16));
	r100_mc_resume(rdev, &save);
}
