si_vram_gtt_location(struct radeon_device *rdev,
			  struct radeon_mc *mc)
{
	if (mc->mc_vram_size > 0xFFC0000000ULL) {

		dev_warn(rdev->dev, "limiting VRAM\n");
		mc->real_vram_size = 0xFFC0000000ULL;
		mc->mc_vram_size = 0xFFC0000000ULL;
	}
	radeon_vram_location(rdev, &rdev->mc, 0);
	rdev->mc.gtt_base_align = 0;
	radeon_gtt_location(rdev, mc);
}
