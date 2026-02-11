handle_ir_buffer_fill(struct context *context,
				 struct descriptor *d,
				 struct descriptor *last)
{
	struct iso_context *ctx =
		container_of(context, struct iso_context, context);
	unsigned int req_count, res_count, completed;
	u32 buffer_dma;

	req_count = le16_to_cpu(last->req_count);
	res_count = le16_to_cpu(ACCESS_ONCE(last->res_count));
	completed = req_count - res_count;
	buffer_dma = le32_to_cpu(last->data_address);

	if (completed > 0) {
		ctx->mc_buffer_bus = buffer_dma;
		ctx->mc_completed = completed;
	}

	if (res_count != 0)

		return 0;

	dma_sync_single_range_for_cpu(context->ohci->card.device,
				      buffer_dma & PAGE_MASK,
				      buffer_dma & ~PAGE_MASK,
				      completed, DMA_FROM_DEVICE);

	if (last->control & cpu_to_le16(DESCRIPTOR_IRQ_ALWAYS)) {
		ctx->base.callback.mc(&ctx->base,
				      buffer_dma + completed,
				      ctx->base.callback_data);
		ctx->mc_completed = 0;
	}

	return 1;
}
