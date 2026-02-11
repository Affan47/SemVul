free_iommu_all(void)
{
	struct amd_iommu *iommu, *next;

	for_each_iommu_safe(iommu, next) {
		list_del(&iommu->list);
		free_iommu_one(iommu);
		kfree(iommu);
	}
}
