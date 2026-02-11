btc_init_stutter_mode(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 tmp;

	if (pi->mclk_stutter_mode_threshold) {
		if (pi->mem_gddr5) {
			tmp = RREG32(MC_PMG_AUTO_CFG);
			if ((0x200 & tmp) == 0) {
				tmp = (tmp & 0xfffffc0b) | 0x204;
				WREG32(MC_PMG_AUTO_CFG, tmp);
			}
		}
	}
}
