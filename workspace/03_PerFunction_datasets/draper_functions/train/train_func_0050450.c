rt2x00queue_map_txskb(struct queue_entry *entry)
{
	struct device *dev = entry->queue->rt2x00dev->dev;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);

	skbdesc->skb_dma =
	    dma_map_single(dev, entry->skb->data, entry->skb->len, DMA_TO_DEVICE);

	if (unlikely(dma_mapping_error(dev, skbdesc->skb_dma)))
		return -ENOMEM;

	skbdesc->flags |= SKBDESC_DMA_MAPPED_TX;
	return 0;
}
