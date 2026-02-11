bdisp_job_finish(struct bdisp_ctx *ctx, int vb_state)
{
	struct vb2_v4l2_buffer *src_vb, *dst_vb;

	if (WARN(!ctx || !ctx->fh.m2m_ctx, "Null hardware context\n"))
		return;

	dev_dbg(ctx->bdisp_dev->dev, "%s\n", __func__);

	src_vb = v4l2_m2m_src_buf_remove(ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_remove(ctx->fh.m2m_ctx);

	if (src_vb && dst_vb) {
		dst_vb->timestamp = src_vb->timestamp;
		dst_vb->timecode = src_vb->timecode;
		dst_vb->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		dst_vb->flags |= src_vb->flags &
					  V4L2_BUF_FLAG_TSTAMP_SRC_MASK;

		v4l2_m2m_buf_done(src_vb, vb_state);
		v4l2_m2m_buf_done(dst_vb, vb_state);

		v4l2_m2m_job_finish(ctx->bdisp_dev->m2m.m2m_dev,
				    ctx->fh.m2m_ctx);
	}
}
