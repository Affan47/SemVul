c2_rx_interrupt(struct net_device *netdev)
{
	struct c2_port *c2_port = netdev_priv(netdev);
	struct c2_dev *c2dev = c2_port->c2dev;
	struct c2_ring *rx_ring = &c2_port->rx_ring;
	struct c2_element *elem;
	struct c2_rx_desc *rx_desc;
	struct c2_rxp_hdr *rxp_hdr;
	struct sk_buff *skb;
	dma_addr_t mapaddr;
	u32 maplen, buflen;
	unsigned long flags;

	spin_lock_irqsave(&c2dev->lock, flags);


	rx_ring->to_clean = rx_ring->start + c2dev->cur_rx;

	for (elem = rx_ring->to_clean; elem->next != rx_ring->to_clean;
	     elem = elem->next) {
		rx_desc = elem->ht_desc;
		mapaddr = elem->mapaddr;
		maplen = elem->maplen;
		skb = elem->skb;
		rxp_hdr = (struct c2_rxp_hdr *) skb->data;

		if (rxp_hdr->flags != RXP_HRXD_DONE)
			break;
		buflen = rxp_hdr->len;


		if (rxp_hdr->status != RXP_HRXD_OK ||
		    buflen > (rx_desc->len - sizeof(*rxp_hdr))) {
			c2_rx_error(c2_port, elem);
			continue;
		}


		if (c2_rx_alloc(c2_port, elem)) {
			c2_rx_error(c2_port, elem);
			continue;
		}


		pci_unmap_single(c2dev->pcidev, mapaddr, maplen,
				 PCI_DMA_FROMDEVICE);

		prefetch(skb->data);


		skb->data += sizeof(*rxp_hdr);
		skb_set_tail_pointer(skb, buflen);
		skb->len = buflen;
		skb->protocol = eth_type_trans(skb, netdev);

		netif_rx(skb);

		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += buflen;
	}


	rx_ring->to_clean = elem;
	c2dev->cur_rx = elem - rx_ring->start;
	C2_SET_CUR_RX(c2dev, c2dev->cur_rx);

	spin_unlock_irqrestore(&c2dev->lock, flags);
}
