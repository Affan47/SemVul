free_freelQ_buffers(struct pci_dev *pdev, struct freelQ *q)
{
	unsigned int cidx = q->cidx;

	while (q->credits--) {
		struct freelQ_ce *ce = &q->centries[cidx];

		pci_unmap_single(pdev, dma_unmap_addr(ce, dma_addr),
				 dma_unmap_len(ce, dma_len),
				 PCI_DMA_FROMDEVICE);
		dev_kfree_skb(ce->skb);
		ce->skb = NULL;
		if (++cidx == q->size)
			cidx = 0;
	}
}
