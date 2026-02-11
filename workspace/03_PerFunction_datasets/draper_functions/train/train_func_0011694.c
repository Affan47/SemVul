de_refill_rx (struct de_private *de)
{
	unsigned i;

	for (i = 0; i < DE_RX_RING_SIZE; i++) {
		struct sk_buff *skb;

		skb = netdev_alloc_skb(de->dev, de->rx_buf_sz);
		if (!skb)
			goto err_out;

		de->rx_skb[i].mapping = pci_map_single(de->pdev,
			skb->data, de->rx_buf_sz, PCI_DMA_FROMDEVICE);
		de->rx_skb[i].skb = skb;

		de->rx_ring[i].opts1 = cpu_to_le32(DescOwn);
		if (i == (DE_RX_RING_SIZE - 1))
			de->rx_ring[i].opts2 =
				cpu_to_le32(RingEnd | de->rx_buf_sz);
		else
			de->rx_ring[i].opts2 = cpu_to_le32(de->rx_buf_sz);
		de->rx_ring[i].addr1 = cpu_to_le32(de->rx_skb[i].mapping);
		de->rx_ring[i].addr2 = 0;
	}

	return 0;

err_out:
	de_clean_rings(de);
	return -ENOMEM;
}
