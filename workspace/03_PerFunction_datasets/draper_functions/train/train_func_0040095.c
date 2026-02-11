free_irte(u16 devid, int index)
{
	struct irq_remap_table *table;
	struct amd_iommu *iommu;
	unsigned long flags;

	iommu = amd_iommu_rlookup_table[devid];
	if (iommu == NULL)
		return;

	table = get_irq_table(devid, false);
	if (!table)
		return;

	spin_lock_irqsave(&table->lock, flags);
	table->table[index] = 0;
	spin_unlock_irqrestore(&table->lock, flags);

	iommu_flush_irt(iommu, devid);
	iommu_completion_wait(iommu);
}
