cik_pcie_init_compute_vmid(struct radeon_device *rdev)
{
	int i;
	uint32_t sh_mem_bases, sh_mem_config;

	sh_mem_bases = 0x6000 | 0x6000 << 16;
	sh_mem_config = ALIGNMENT_MODE(SH_MEM_ALIGNMENT_MODE_UNALIGNED);
	sh_mem_config |= DEFAULT_MTYPE(MTYPE_NONCACHED);

	mutex_lock(&rdev->srbm_mutex);
	for (i = 8; i < 16; i++) {
		cik_srbm_select(rdev, 0, 0, 0, i);

		WREG32(SH_MEM_CONFIG, sh_mem_config);
		WREG32(SH_MEM_APE1_BASE, 1);
		WREG32(SH_MEM_APE1_LIMIT, 0);
		WREG32(SH_MEM_BASES, sh_mem_bases);
	}
	cik_srbm_select(rdev, 0, 0, 0, 0);
	mutex_unlock(&rdev->srbm_mutex);
}
