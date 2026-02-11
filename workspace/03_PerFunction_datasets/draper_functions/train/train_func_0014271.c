cw1200_tx_h_align(struct cw1200_common *priv,
		  struct cw1200_txinfo *t,
		  u8 *flags)
{
	size_t offset = (size_t)t->skb->data & 3;

	if (!offset)
		return 0;

	if (offset & 1) {
		wiphy_err(priv->hw->wiphy,
			  "Bug: attempt to transmit a frame with wrong alignment: %zu\n",
			  offset);
		return -EINVAL;
	}

	if (skb_headroom(t->skb) < offset) {
		wiphy_err(priv->hw->wiphy,
			  "Bug: no space allocated for DMA alignment. headroom: %d\n",
			  skb_headroom(t->skb));
		return -ENOMEM;
	}
	skb_push(t->skb, offset);
	t->hdrlen += offset;
	t->txpriv.offset += offset;
	*flags |= WSM_TX_2BYTES_SHIFT;
	cw1200_debug_tx_align(priv);
	return 0;
}
