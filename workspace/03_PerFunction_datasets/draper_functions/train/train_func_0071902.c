dwceqos_tx_linear(struct sk_buff *skb, struct net_local *lp,
			     struct dwceqos_tx *tx)
{
	struct ring_desc *rd;
	struct dwceqos_dma_desc *dd;
	size_t payload_len;
	dma_addr_t dma_handle;

	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_size != lp->gso_size) {
		dwceqos_dmadesc_set_ctx(lp, skb_shinfo(skb)->gso_size);
		lp->gso_size = skb_shinfo(skb)->gso_size;
	}

	dma_handle = dma_map_single(lp->ndev->dev.parent, skb->data,
				    skb_headlen(skb), DMA_TO_DEVICE);

	if (dma_mapping_error(lp->ndev->dev.parent, dma_handle)) {
		netdev_err(lp->ndev, "TX DMA Mapping error\n");
		return -ENOMEM;
	}

	rd = &lp->tx_skb[lp->tx_next];
	dd = &lp->tx_descs[lp->tx_next];

	rd->skb = NULL;
	rd->len = skb_headlen(skb);
	rd->mapping = dma_handle;


	dd->des0 = dma_handle;

	if (skb_is_gso(skb)) {
		payload_len = skb_headlen(skb) - tx->network_header_len;

		if (payload_len)
			dd->des1 = dma_handle + tx->network_header_len;
		dd->des2 = tx->network_header_len |
			DWCEQOS_DMA_DES2_B2L(payload_len);
		dd->des3 = DWCEQOS_DMA_TDES3_TSE |
			DWCEQOS_DMA_DES3_THL((tcp_hdrlen(skb) / 4)) |
			(skb->len - tx->network_header_len);
	} else {
		dd->des1 = 0;
		dd->des2 = skb_headlen(skb);
		dd->des3 = skb->len;

		switch (skb->ip_summed) {
		case CHECKSUM_PARTIAL:
			dd->des3 |= DWCEQOS_DMA_TDES3_CA;
		case CHECKSUM_NONE:
		case CHECKSUM_UNNECESSARY:
		case CHECKSUM_COMPLETE:
		default:
			break;
		}
	}

	dd->des3 |= DWCEQOS_DMA_TDES3_FD;
	if (lp->tx_next  != tx->initial_descriptor)
		dd->des3 |= DWCEQOS_DMA_TDES3_OWN;

	tx->last_descriptor = lp->tx_next;
	lp->tx_next = (lp->tx_next + 1) % DWCEQOS_TX_DCNT;

	return 0;
}
