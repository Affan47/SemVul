radeon_dummy_page_init(struct radeon_device *rdev)
{
	if (rdev->dummy_page.page)
		return 0;
	rdev->dummy_page.page = alloc_page(GFP_DMA32 | GFP_KERNEL | __GFP_ZERO);
	if (rdev->dummy_page.page == NULL)
		return -ENOMEM;
	rdev->dummy_page.addr = pci_map_page(rdev->pdev, rdev->dummy_page.page,
					0, PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
	if (pci_dma_mapping_error(rdev->pdev, rdev->dummy_page.addr)) {
		dev_err(&rdev->pdev->dev, "Failed to DMA MAP the dummy page\n");
		__free_page(rdev->dummy_page.page);
		rdev->dummy_page.page = NULL;
		return -ENOMEM;
	}
	rdev->dummy_page.entry = radeon_gart_get_page_entry(rdev->dummy_page.addr,
							    RADEON_GART_PAGE_DUMMY);
	return 0;
}
