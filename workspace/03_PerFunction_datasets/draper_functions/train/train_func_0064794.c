get_ir_irq_domain(struct irq_alloc_info *info)
{
	struct amd_iommu *iommu;
	int devid;

	if (!info)
		return NULL;

	devid = get_devid(info);
	if (devid >= 0) {
		iommu = amd_iommu_rlookup_table[devid];
		if (iommu)
			return iommu->ir_domain;
	}

	return NULL;
}
