r6040_alloc_rxbufs(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	struct r6040_descriptor *desc;
	struct sk_buff *skb;
	int rc;

	lp->rx_remove_ptr = lp->rx_insert_ptr = lp->rx_ring;
	r6040_init_ring_desc(lp->rx_ring, lp->rx_ring_dma, RX_DCNT);


	desc = lp->rx_ring;
	do {
		skb = netdev_alloc_skb(dev, MAX_BUF_SIZE);
		if (!skb) {
			rc = -ENOMEM;
			goto err_exit;
		}
		desc->skb_ptr = skb;
		desc->buf = cpu_to_le32(pci_map_single(lp->pdev,
					desc->skb_ptr->data,
					MAX_BUF_SIZE, PCI_DMA_FROMDEVICE));
		desc->status = DSC_OWNER_MAC;
		desc = desc->vndescp;
	} while (desc != lp->rx_ring);

	return 0;

err_exit:

	r6040_free_rxbufs(dev);
	return rc;
}
