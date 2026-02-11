setup_rx_descbuffer(struct b43legacy_dmaring *ring,
			       struct b43legacy_dmadesc32 *desc,
			       struct b43legacy_dmadesc_meta *meta,
			       gfp_t gfp_flags)
{
	struct b43legacy_rxhdr_fw3 *rxhdr;
	struct b43legacy_hwtxstatus *txstat;
	dma_addr_t dmaaddr;
	struct sk_buff *skb;

	B43legacy_WARN_ON(ring->tx);

	skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
	if (unlikely(!skb))
		return -ENOMEM;
	dmaaddr = map_descbuffer(ring, skb->data,
				 ring->rx_buffersize, 0);
	if (b43legacy_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) {

		gfp_flags |= GFP_DMA;

		dev_kfree_skb_any(skb);

		skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
		if (unlikely(!skb))
			return -ENOMEM;
		dmaaddr = map_descbuffer(ring, skb->data,
					 ring->rx_buffersize, 0);
	}

	if (b43legacy_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) {
		dev_kfree_skb_any(skb);
		return -EIO;
	}

	meta->skb = skb;
	meta->dmaaddr = dmaaddr;
	op32_fill_descriptor(ring, desc, dmaaddr, ring->rx_buffersize, 0, 0, 0);

	rxhdr = (struct b43legacy_rxhdr_fw3 *)(skb->data);
	rxhdr->frame_len = 0;
	txstat = (struct b43legacy_hwtxstatus *)(skb->data);
	txstat->cookie = 0;

	return 0;
}
