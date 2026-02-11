ir_remove_ioapic_hpet_scope(struct intel_iommu *iommu)
{
	int i;

	for (i = 0; i < MAX_HPET_TBS; i++)
		if (ir_hpet[i].iommu == iommu)
			ir_hpet[i].iommu = NULL;

	for (i = 0; i < MAX_IO_APICS; i++)
		if (ir_ioapic[i].iommu == iommu)
			ir_ioapic[i].iommu = NULL;
}
