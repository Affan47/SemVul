drm_ati_pcigart_cleanup(struct drm_device *dev, struct drm_ati_pcigart_info *gart_info)
{
	struct drm_sg_mem *entry = dev->sg;
	unsigned long pages;
	int i;
	int max_pages;


	if (!entry) {
		DRM_ERROR("no scatter/gather memory!\n");
		return 0;
	}

	if (gart_info->bus_addr) {

		max_pages = (gart_info->table_size / sizeof(u32));
		pages = (entry->pages <= max_pages)
		  ? entry->pages : max_pages;

		for (i = 0; i < pages; i++) {
			if (!entry->busaddr[i])
				break;
			pci_unmap_page(dev->pdev, entry->busaddr[i],
					 PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
		}

		if (gart_info->gart_table_location == DRM_ATI_GART_MAIN)
			gart_info->bus_addr = 0;
	}

	if (gart_info->gart_table_location == DRM_ATI_GART_MAIN &&
	    gart_info->table_handle) {
		drm_ati_free_pcigart_table(dev, gart_info);
	}

	return 1;
}
