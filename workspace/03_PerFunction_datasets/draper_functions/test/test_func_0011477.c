rr_raz_tx(struct rr_private *rrpriv,
			     struct net_device *dev)
{
	int i;

	for (i = 0; i < TX_RING_ENTRIES; i++) {
		struct sk_buff *skb = rrpriv->tx_skbuff[i];

		if (skb) {
			struct tx_desc *desc = &(rrpriv->tx_ring[i]);

	        	pci_unmap_single(rrpriv->pci_dev, desc->addr.addrlo,
				skb->len, PCI_DMA_TODEVICE);
			desc->size = 0;
			set_rraddr(&desc->addr, 0);
			dev_kfree_skb(skb);
			rrpriv->tx_skbuff[i] = NULL;
		}
	}
}
