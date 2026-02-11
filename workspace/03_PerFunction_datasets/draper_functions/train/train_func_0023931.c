init_iommu_perf_ctr(struct amd_iommu *iommu)
{
	u64 val = 0xabcd, val2 = 0;

	if (!iommu_feature(iommu, FEATURE_PC))
		return;

	amd_iommu_pc_present = true;


	if ((0 != iommu_pc_get_set_reg_val(iommu, 0, 0, 0, &val, true)) ||
	    (0 != iommu_pc_get_set_reg_val(iommu, 0, 0, 0, &val2, false)) ||
	    (val != val2)) {
		pr_err("AMD-Vi: Unable to write to IOMMU perf counter.\n");
		amd_iommu_pc_present = false;
		return;
	}

	pr_info("AMD-Vi: IOMMU performance counters supported\n");

	val = readl(iommu->mmio_base + MMIO_CNTR_CONF_OFFSET);
	iommu->max_banks = (u8) ((val >> 12) & 0x3f);
	iommu->max_counters = (u8) ((val >> 7) & 0xf);
}
