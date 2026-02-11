ksz_init_rx_buffers(struct dev_info *adapter)
{
	int i;
	struct ksz_desc *desc;
	struct ksz_dma_buf *dma_buf;
	struct ksz_hw *hw = &adapter->hw;
	struct ksz_desc_info *info = &hw->rx_desc_info;

	for (i = 0; i < hw->rx_desc_info.alloc; i++) {
		get_rx_pkt(info, &desc);

		dma_buf = DMA_BUFFER(desc);
		if (dma_buf->skb && dma_buf->len != adapter->mtu)
			free_dma_buf(adapter, dma_buf, PCI_DMA_FROMDEVICE);
		dma_buf->len = adapter->mtu;
		if (!dma_buf->skb)
			dma_buf->skb = alloc_skb(dma_buf->len, GFP_ATOMIC);
		if (dma_buf->skb && !dma_buf->dma)
			dma_buf->dma = pci_map_single(
				adapter->pdev,
				skb_tail_pointer(dma_buf->skb),
				dma_buf->len,
				PCI_DMA_FROMDEVICE);


		set_rx_buf(desc, dma_buf->dma);
		set_rx_len(desc, dma_buf->len);
		release_desc(desc);
	}
}
