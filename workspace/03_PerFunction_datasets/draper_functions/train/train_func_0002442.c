uninit_device_table_dma(void)
{
	u32 devid;

	for (devid = 0; devid <= amd_iommu_last_bdf; ++devid) {
		amd_iommu_dev_table[devid].data[0] = 0ULL;
		amd_iommu_dev_table[devid].data[1] = 0ULL;
	}
}
