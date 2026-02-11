init_iommu_group(struct device *dev)
{
	struct dma_ops_domain *dma_domain;
	struct iommu_domain *domain;
	struct iommu_group *group;

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return;

	domain = iommu_group_default_domain(group);
	if (!domain)
		goto out;

	if (to_pdomain(domain)->flags == PD_DMA_OPS_MASK) {
		dma_domain = to_pdomain(domain)->priv;
		init_unity_mappings_for_device(dev, dma_domain);
	}

out:
	iommu_group_put(group);
}
