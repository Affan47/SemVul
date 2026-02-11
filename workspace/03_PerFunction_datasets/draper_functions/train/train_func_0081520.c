at_context_transmit(struct context *ctx, struct fw_packet *packet)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctx->ohci->lock, flags);

	if (HEADER_GET_DESTINATION(packet->header[0]) == ctx->ohci->node_id &&
	    ctx->ohci->generation == packet->generation) {
		spin_unlock_irqrestore(&ctx->ohci->lock, flags);
		handle_local_request(ctx, packet);
		return;
	}

	ret = at_context_queue_packet(ctx, packet);
	spin_unlock_irqrestore(&ctx->ohci->lock, flags);

	if (ret < 0)
		packet->callback(packet, &ctx->ohci->card, packet->ack);

}
