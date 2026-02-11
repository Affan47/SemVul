s5p_mfc_run_init_enc(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;
	struct s5p_mfc_buf *dst_mb;
	unsigned long dst_addr;
	unsigned int dst_size;

	s5p_mfc_set_enc_ref_buffer_v5(ctx);
	spin_lock_irqsave(&dev->irqlock, flags);
	dst_mb = list_entry(ctx->dst_queue.next, struct s5p_mfc_buf, list);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_plane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_set_enc_stream_buffer_v5(ctx, dst_addr, dst_size);
	spin_unlock_irqrestore(&dev->irqlock, flags);
	dev->curr_ctx = ctx->num;
	s5p_mfc_init_encode_v5(ctx);
}
