ipoib_dma_unmap_tx(struct ipoib_dev_priv *priv,
			struct ipoib_tx_buf *tx_req)
{
	struct sk_buff *skb = tx_req->skb;
	u64 *mapping = tx_req->mapping;
	int i;
	int off;

	if (skb_headlen(skb)) {
		ib_dma_unmap_single(priv->ca, mapping[0], skb_headlen(skb),
				    DMA_TO_DEVICE);
		off = 1;
	} else
		off = 0;

	for (i = 0; i < skb_shinfo(skb)->nr_frags; ++i) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		ib_dma_unmap_page(priv->ca, mapping[i + off],
				  skb_frag_size(frag), DMA_TO_DEVICE);
	}
}
