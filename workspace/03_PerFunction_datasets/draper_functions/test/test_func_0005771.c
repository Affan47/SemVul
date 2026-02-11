jpu_buf_finish(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct jpu_buffer *jpu_buf = vb2_to_jpu_buffer(vbuf);
	struct jpu_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct jpu_q_data *q_data = &ctx->out_q;
	enum v4l2_buf_type type = vb->vb2_queue->type;
	u8 *buffer;

	if (vb->state == VB2_BUF_STATE_DONE)
		vbuf->sequence = jpu_get_q_data(ctx, type)->sequence++;

	if (!ctx->encoder || vb->state != VB2_BUF_STATE_DONE ||
	    V4L2_TYPE_IS_OUTPUT(type))
		return;

	buffer = vb2_plane_vaddr(vb, 0);

	memcpy(buffer, jpeg_hdrs[jpu_buf->compr_quality], JPU_JPEG_HDR_SIZE);
	*(__be16 *)(buffer + JPU_JPEG_HEIGHT_OFFSET) =
					cpu_to_be16(q_data->format.height);
	*(__be16 *)(buffer + JPU_JPEG_WIDTH_OFFSET) =
					cpu_to_be16(q_data->format.width);
	*(buffer + JPU_JPEG_SUBS_OFFSET) = q_data->fmtinfo->subsampling;
}
