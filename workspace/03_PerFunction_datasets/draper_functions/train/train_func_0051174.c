octeon_delete_droq(struct octeon_device *oct, u32 q_no)
{
	struct octeon_droq *droq = oct->droq[q_no];

	dev_dbg(&oct->pci_dev->dev, "%s[%d]\n", __func__, q_no);

	octeon_droq_destroy_ring_buffers(oct, droq);
	vfree(droq->recv_buf_list);

	if (droq->info_base_addr)
		cnnic_free_aligned_dma(oct->pci_dev, droq->info_list,
				       droq->info_alloc_size,
				       droq->info_base_addr,
				       droq->info_list_dma);

	if (droq->desc_ring)
		lio_dma_free(oct, (droq->max_count * OCT_DROQ_DESC_SIZE),
			     droq->desc_ring, droq->desc_ring_dma);

	memset(droq, 0, OCT_DROQ_SIZE);

	return 0;
}
