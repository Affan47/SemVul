vidioc_expbuf(struct file *file, void *priv,
	struct v4l2_exportbuffer *eb)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	if (eb->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return vb2_expbuf(&ctx->vq_src, eb);
	if (eb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return vb2_expbuf(&ctx->vq_dst, eb);
	return -EINVAL;
}
