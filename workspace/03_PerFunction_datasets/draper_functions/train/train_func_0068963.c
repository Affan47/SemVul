iommu_enable_command_buffer(struct amd_iommu *iommu)
{
	u64 entry;

	BUG_ON(iommu->cmd_buf == NULL);

	entry = (u64)virt_to_phys(iommu->cmd_buf);
	entry |= MMIO_CMD_SIZE_512;

	memcpy_toio(iommu->mmio_base + MMIO_CMD_BUF_OFFSET,
		    &entry, sizeof(entry));

	amd_iommu_reset_cmd_buffer(iommu);
}
