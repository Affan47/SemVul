sis190_try_rx_copy(struct sis190_private *tp,
			       struct sk_buff **sk_buff, int pkt_size,
			       dma_addr_t addr)
{
	struct sk_buff *skb;
	bool done = false;

	if (pkt_size >= rx_copybreak)
		goto out;

	skb = netdev_alloc_skb_ip_align(tp->dev, pkt_size);
	if (!skb)
		goto out;

	pci_dma_sync_single_for_cpu(tp->pci_dev, addr, tp->rx_buf_sz,
				PCI_DMA_FROMDEVICE);
	skb_copy_to_linear_data(skb, sk_buff[0]->data, pkt_size);
	*sk_buff = skb;
	done = true;
out:
	return done;
}
