ar_recycle_buffers(struct ar_context *ctx, unsigned int end_buffer)
{
	unsigned int i;

	i = ar_first_buffer_index(ctx);
	while (i != end_buffer) {
		dma_sync_single_for_device(ctx->ohci->card.device,
					   ar_buffer_bus(ctx, i),
					   PAGE_SIZE, DMA_FROM_DEVICE);
		ar_context_link_page(ctx, i);
		i = ar_next_buffer_index(i);
	}
}
