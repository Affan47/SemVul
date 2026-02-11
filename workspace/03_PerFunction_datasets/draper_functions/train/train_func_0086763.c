nv_unmap_txskb(struct fe_priv *np, struct nv_skb_map *tx_skb)
{
	if (tx_skb->dma) {
		if (tx_skb->dma_single)
			pci_unmap_single(np->pci_dev, tx_skb->dma,
					 tx_skb->dma_len,
					 PCI_DMA_TODEVICE);
		else
			pci_unmap_page(np->pci_dev, tx_skb->dma,
				       tx_skb->dma_len,
				       PCI_DMA_TODEVICE);
		tx_skb->dma = 0;
	}
}
