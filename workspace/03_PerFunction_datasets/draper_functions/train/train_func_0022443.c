jpu_cleanup(struct jpu_ctx *ctx, bool reset)
{

	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	unsigned long flags;

	spin_lock_irqsave(&ctx->jpu->lock, flags);

	src_buf = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);

	v4l2_m2m_buf_done(src_buf, VB2_BUF_STATE_ERROR);
	v4l2_m2m_buf_done(dst_buf, VB2_BUF_STATE_ERROR);


	if (reset)
		jpu_write(ctx->jpu, JCCMD_SRST, JCCMD);

	spin_unlock_irqrestore(&ctx->jpu->lock, flags);

	v4l2_m2m_job_finish(ctx->jpu->m2m_dev, ctx->fh.m2m_ctx);
}
