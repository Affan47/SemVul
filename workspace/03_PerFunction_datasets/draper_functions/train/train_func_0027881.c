bdisp_buf_prepare(struct vb2_buffer *vb)
{
	struct bdisp_ctx *ctx = vb2_get_drv_priv(vb->vb2_queue);
	struct bdisp_frame *frame = ctx_get_frame(ctx, vb->vb2_queue->type);

	if (IS_ERR(frame)) {
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		return PTR_ERR(frame);
	}

	if (vb->vb2_queue->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		vb2_set_plane_payload(vb, 0, frame->sizeimage);

	return 0;
}
