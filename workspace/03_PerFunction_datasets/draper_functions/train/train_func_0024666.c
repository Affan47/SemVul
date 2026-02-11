bnxt_copy_skb(struct bnxt_napi *bnapi, u8 *data,
					    unsigned int len,
					    dma_addr_t mapping)
{
	struct bnxt *bp = bnapi->bp;
	struct pci_dev *pdev = bp->pdev;
	struct sk_buff *skb;

	skb = napi_alloc_skb(&bnapi->napi, len);
	if (!skb)
		return NULL;

	dma_sync_single_for_cpu(&pdev->dev, mapping, bp->rx_copy_thresh,
				bp->rx_dir);

	memcpy(skb->data - NET_IP_ALIGN, data - NET_IP_ALIGN,
	       len + NET_IP_ALIGN);

	dma_sync_single_for_device(&pdev->dev, mapping, bp->rx_copy_thresh,
				   bp->rx_dir);

	skb_put(skb, len);
	return skb;
}
