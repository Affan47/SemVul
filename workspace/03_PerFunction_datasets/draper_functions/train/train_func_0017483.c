rv6xx_enable_pcie_gen2_support(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = RREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL);

	if ((tmp & LC_OTHER_SIDE_EVER_SENT_GEN2) &&
	    (tmp & LC_OTHER_SIDE_SUPPORTS_GEN2)) {
		tmp |= LC_GEN2_EN;
		WREG32_PCIE_PORT(PCIE_LC_SPEED_CNTL, tmp);
	}
}
