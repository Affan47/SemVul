pch_gbe_unmap_and_free_tx_resource(
	struct pch_gbe_adapter *adapter, struct pch_gbe_buffer *buffer_info)
{
	if (buffer_info->mapped) {
		dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
				 buffer_info->length, DMA_TO_DEVICE);
		buffer_info->mapped = false;
	}
	if (buffer_info->skb) {
		dev_kfree_skb_any(buffer_info->skb);
		buffer_info->skb = NULL;
	}
}
