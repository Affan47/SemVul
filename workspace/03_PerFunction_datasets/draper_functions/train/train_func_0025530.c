calgary_iommu_init(void)
{
	int ret;


	printk(KERN_INFO "PCI-DMA: Using Calgary IOMMU\n");

	ret = calgary_init();
	if (ret) {
		printk(KERN_ERR "PCI-DMA: Calgary init failed %d, "
		       "falling back to no_iommu\n", ret);
		return ret;
	}

	return 0;
}
