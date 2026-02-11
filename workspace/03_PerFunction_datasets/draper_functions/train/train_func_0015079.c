r600_get_pcie_gen_support(struct radeon_device *rdev,
					       u32 sys_mask,
					       enum radeon_pcie_gen asic_gen,
					       enum radeon_pcie_gen default_gen)
{
	switch (asic_gen) {
	case RADEON_PCIE_GEN1:
		return RADEON_PCIE_GEN1;
	case RADEON_PCIE_GEN2:
		return RADEON_PCIE_GEN2;
	case RADEON_PCIE_GEN3:
		return RADEON_PCIE_GEN3;
	default:
		if ((sys_mask & DRM_PCIE_SPEED_80) && (default_gen == RADEON_PCIE_GEN3))
			return RADEON_PCIE_GEN3;
		else if ((sys_mask & DRM_PCIE_SPEED_50) && (default_gen == RADEON_PCIE_GEN2))
			return RADEON_PCIE_GEN2;
		else
			return RADEON_PCIE_GEN1;
	}
	return RADEON_PCIE_GEN1;
}
