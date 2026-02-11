e100_rx_clean_list(struct nic *nic)
{
	struct rx *rx;
	unsigned int i, count = nic->params.rfds.count;

	nic->ru_running = RU_UNINITIALIZED;

	if (nic->rxs) {
		for (rx = nic->rxs, i = 0; i < count; rx++, i++) {
			if (rx->skb) {
				pci_unmap_single(nic->pdev, rx->dma_addr,
					RFD_BUF_LEN, PCI_DMA_BIDIRECTIONAL);
				dev_kfree_skb(rx->skb);
			}
		}
		kfree(nic->rxs);
		nic->rxs = NULL;
	}

	nic->rx_to_use = nic->rx_to_clean = NULL;
}
