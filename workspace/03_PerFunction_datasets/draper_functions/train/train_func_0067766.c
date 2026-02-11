iommu_unmap_mmio_space(struct amd_iommu *iommu)
{
	if (iommu->mmio_base)
		iounmap(iommu->mmio_base);
	release_mem_region(iommu->mmio_phys, iommu->mmio_phys_end);
}
