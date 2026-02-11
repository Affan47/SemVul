pci_xen_swiotlb_detect(void)
{

	if (!xen_pv_domain())
		return 0;


	if ((xen_initial_domain() || swiotlb || swiotlb_force))
		xen_swiotlb = 1;


	swiotlb = 0;

#ifdef CONFIG_X86_64


	if (max_pfn > MAX_DMA32_PFN)
		no_iommu = 1;
#endif
	return xen_swiotlb;
}
