modify_irte(u16 devid, int index, union irte irte)
{
	struct irq_remap_table *table;
	struct amd_iommu *iommu;
	unsigned long flags;

	iommu = amd_iommu_rlookup_table[devid];
	if (iommu == NULL)
		return -EINVAL;

	table = get_irq_table(devid, false);
	if (!table)
		return -ENOMEM;

	spin_lock_irqsave(&table->lock, flags);
	table->table[index] = irte.val;
	spin_unlock_irqrestore(&table->lock, flags);

	iommu_flush_irt(iommu, devid);
	iommu_completion_wait(iommu);

	return 0;
}
