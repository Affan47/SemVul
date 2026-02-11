iommu_get_dm_regions(struct device *dev, struct list_head *list)
{
	const struct iommu_ops *ops = dev->bus->iommu_ops;

	if (ops && ops->get_dm_regions)
		ops->get_dm_regions(dev, list);
}
