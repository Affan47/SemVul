scif_iommu_map(struct scif_dev *remote_dev,
			  struct scif_window *window)
{
	struct scatterlist *sg;
	int i, err;
	scif_pinned_pages_t pin = window->pinned_pages;

	window->st = kzalloc(sizeof(*window->st), GFP_KERNEL);
	if (!window->st)
		return -ENOMEM;

	err = sg_alloc_table(window->st, window->nr_pages, GFP_KERNEL);
	if (err)
		return err;

	for_each_sg(window->st->sgl, sg, window->st->nents, i)
		sg_set_page(sg, pin->pages[i], PAGE_SIZE, 0x0);

	err = dma_map_sg(&remote_dev->sdev->dev, window->st->sgl,
			 window->st->nents, DMA_BIDIRECTIONAL);
	if (!err)
		return -ENOMEM;

	sg = window->st->sgl;
	for (i = 0; sg; i++) {
		dma_addr_t last_da;

		window->dma_addr[i] = sg_dma_address(sg);
		window->num_pages[i] = sg_dma_len(sg) >> PAGE_SHIFT;
		last_da = sg_dma_address(sg) + sg_dma_len(sg);
		while ((sg = sg_next(sg)) && sg_dma_address(sg) == last_da) {
			window->num_pages[i] +=
				(sg_dma_len(sg) >> PAGE_SHIFT);
			last_da = window->dma_addr[i] +
				sg_dma_len(sg);
		}
		window->nr_contig_chunks++;
	}
	return 0;
}
