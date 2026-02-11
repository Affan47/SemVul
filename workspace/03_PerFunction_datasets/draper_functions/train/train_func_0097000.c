rocker_dma_ring_bufs_free(const struct rocker *rocker,
				      const struct rocker_dma_ring_info *info,
				      int direction)
{
	struct pci_dev *pdev = rocker->pdev;
	int i;

	for (i = 0; i < info->size; i++) {
		const struct rocker_desc_info *desc_info = &info->desc_info[i];
		struct rocker_desc *desc = &info->desc[i];

		desc->buf_addr = 0;
		desc->buf_size = 0;
		pci_unmap_single(pdev, dma_unmap_addr(desc_info, mapaddr),
				 desc_info->data_size, direction);
		kfree(desc_info->data);
	}
}
