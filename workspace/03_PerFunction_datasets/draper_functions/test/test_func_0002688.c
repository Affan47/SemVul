genwqe_map_pages(struct genwqe_dev *cd,
			   struct page **page_list, int num_pages,
			   dma_addr_t *dma_list)
{
	int i;
	struct pci_dev *pci_dev = cd->pci_dev;


	for (i = 0; i < num_pages; i++) {
		dma_addr_t daddr;

		dma_list[i] = 0x0;
		daddr = pci_map_page(pci_dev, page_list[i],
				     0,
				     PAGE_SIZE,
				     PCI_DMA_BIDIRECTIONAL);

		if (pci_dma_mapping_error(pci_dev, daddr)) {
			dev_err(&pci_dev->dev,
				"[%s] err: no dma addr daddr=%016llx!\n",
				__func__, (long long)daddr);
			goto err;
		}

		dma_list[i] = daddr;
	}
	return 0;

 err:
	genwqe_unmap_pages(cd, dma_list, num_pages);
	return -EIO;
}
