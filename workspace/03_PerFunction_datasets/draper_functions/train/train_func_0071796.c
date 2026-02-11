mlx4_en_alloc_frags(struct mlx4_en_priv *priv,
			       struct mlx4_en_rx_desc *rx_desc,
			       struct mlx4_en_rx_alloc *frags,
			       struct mlx4_en_rx_alloc *ring_alloc,
			       gfp_t gfp)
{
	struct mlx4_en_rx_alloc page_alloc[MLX4_EN_MAX_RX_FRAGS];
	const struct mlx4_en_frag_info *frag_info;
	struct page *page;
	dma_addr_t dma;
	int i;

	for (i = 0; i < priv->num_frags; i++) {
		frag_info = &priv->frag_info[i];
		page_alloc[i] = ring_alloc[i];
		page_alloc[i].page_offset += frag_info->frag_stride;

		if (page_alloc[i].page_offset + frag_info->frag_stride <=
		    ring_alloc[i].page_size)
			continue;

		if (mlx4_alloc_pages(priv, &page_alloc[i], frag_info, gfp))
			goto out;
	}

	for (i = 0; i < priv->num_frags; i++) {
		frags[i] = ring_alloc[i];
		dma = ring_alloc[i].dma + ring_alloc[i].page_offset;
		ring_alloc[i] = page_alloc[i];
		rx_desc->data[i].addr = cpu_to_be64(dma);
	}

	return 0;

out:
	while (i--) {
		if (page_alloc[i].page != ring_alloc[i].page) {
			dma_unmap_page(priv->ddev, page_alloc[i].dma,
				page_alloc[i].page_size, PCI_DMA_FROMDEVICE);
			page = page_alloc[i].page;
			atomic_set(&page->_count, 1);
			put_page(page);
		}
	}
	return -ENOMEM;
}
